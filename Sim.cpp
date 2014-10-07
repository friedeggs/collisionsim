#include <vector>
#include <cstdlib>
#include <iterator>
#include <iostream>
#include "Ball.h"
#include "Sim.h"

/** Constructs a simulation of the specified dimensions.
 */
Sim::Sim(int dimensions, bool rotation)
{
	dim = dimensions;
	rot = rotation && dim == 2;		// Right now, we can only do rotation in 2D
	t = 0;
}

/** Adds the specified ball to the simulation.
 */
void Sim::addBall(Ball ball)
{
	balls.push_back(ball);
}

/** Advances the simulation by the specified time step.
 * Computes the new positions and velocities of all 
 * simulated balls through using the laws of phyics.
 */
void Sim::advance(double dt)
{
	// Advance velocity
	for (int i = 0; i < balls.size() - 1; i++) {
		for (int j = i + 1; j < balls.size(); j++) {
			if (collision (balls[i], balls[j])) {
				tick_v(balls[i], balls [j], dt);
			}
		}
	}
	// Advance displacement
	for (int i = 0; i < balls.size(); i++)
	{
		tick_s(balls[i], dt);
	}
	// Advance time
	t += dt;
}

/** Advances the velocity vectors of two colliding balls.
 */
void Sim::tick_v(Ball &b1, Ball &b2, double dt)
{
	// The force constant is derived from Newton's 3rd Law: F1 = F2.
	double force_const = b1.k * b2.k / (b1.k + b2.k);
	vector<double> strain(dim);							// Vector pointing from b1 to b2 of magnitude delta x
	vector<double> ds = b1.dist(b2);					// Vector connecting centres of b1 and b2
	vector<double> relaxed_ds = b1.unstrained_r(b2);	// Ideal unstrained touching distance btwn b1 and b2
	vector<double> force(dim);							// Vector pointing from b1 to b2 of magnitude normal force

	// Compute the compression
	
	for (int i = 0; i < dim; i++)	
		strain[i] = relaxed_ds[i] - ds[i];
		
	// Compute the spring accelerations and adjust v's accordingly
	
	for (int i = 0; i < dim; i++)
	{
		force[i] = strain[i] * force_const;
		b1.v[i] -= (force[i] / b1.m) * dt;
		b2.v[i] += (force[i] / b2.m) * dt;
	}	
	
	// Compute the velocity of the particles on the touching surfaces
	
	if (rot)
	{	
		vector<double> v1_tan(2);	// tangential velocity solely due to w
		vector<double> v2_tan(2);
		vector<double> v1(2);		// summed tangential velocity
		vector<double> v2(2);
		vector<double> r1(2);		// compressed radius vector
		vector<double> r2(2);
		
		// Compute the compressed radius vectors of each ball
		
		for (int i = 0; i < 2; i++)
		{
			r1[i] = b1.r / (b1.r + b2.r) * (relaxed_ds[i]);		// Relaxed r Ball 1
			r1[i] -= strain[i] * force_const / b1.k;			// Subtract Ball 1 compression
	
			r2[i] = -b2.r / (b1.r + b2.r) * (relaxed_ds[i]);	// Relaxed r Ball 2
			r2[i] -= -strain[i] * force_const / b2.k;			// Subtract Ball 2 compression
		}
		
		// Compute the tangential surface velocities due to rotation
		// v_tan = w * r, and v_tan is perpendicular to r...
				
		v1_tan[0] = -r1[1];
		v1_tan[1] = r1[0];		
		v2_tan[0] = -r2[1];
		v2_tan[1] = r2[0];				
					
		// Find the summed tangential component of the surface velocity,
		// taking into account both w and v_com
		
		double const_1 = (dot(v1_tan, b1.v) / sqabs(v1_tan) + b1.w);	
		double const_2 = (dot(v2_tan, b2.v) / sqabs(v2_tan) + b2.w);		
						
		for (int i = 0; i < 2; i++)
		{
			v1[i] = const_1 * v1_tan[i];
			v2[i] = const_2 * v2_tan[i];
		}
		
		// Find the relative tangential velocity, ball 1 to ball 2
		
		v1[0] -= v2[0];
		v1[1] -= v2[1];		
		
		if (v1[0] != 0 || v1[1] != 0) // If relative velocities are nonzero
		{									
			// Compute direction and magnitude of frictional force		
		
			vector<double> f_k(2);		// The friction force vector
			f_k[0] = -force[1] * u_k;
			f_k[1] = force[0] * u_k;
			if (dot(f_k, v1) > 0) // Ensure that friction force points opposite v1
			{
				f_k[0] *= -1;
				f_k[1] *= -1;		
			}
									
			// Compute the torques
			
			double T1 = crossz(r1, f_k);
			double T2 = -crossz(r2, f_k);
			
			// Compute change in angular velocities
			
			double dw1 = T1 * dt / b1.I;
			double dw2 = T2 * dt / b2.I;
				
			// Compute and store new angular velocities
			
			b1.w += dw1;
			b2.w += dw2;
		}
	}
}

/** Advances the position vector of the specified ball
 * as indicated by the ball's current velocity vector.
 */
void Sim::tick_s(Ball &ball, double dt)
{
	for (int i = 0; i < dim; i++)
		ball.s[i] += dt * ball.v[i];	
}

/** Returns true if the two specified balls are in contact.
 */
bool Sim::collision(Ball b1, Ball b2) 
{	
	return sqabs(b1.dist(b2)) < (b1.r + b2.r) * (b1.r + b2.r);
}

/** Computes the z-component of the cross product of the
 * two specified vectors.
 */
double Sim::crossz(vector<double> a, vector<double> b)
{
	return (a[0] * b[1]) - (a[1] * b[0]);	
}


/** Computes the dot product of the two specified vectors.
 */
double Sim::dot(vector<double> a, vector<double> b)
{
	double sum = 0;
	for (int i = 0; i < a.size(); i++)
		sum += a[i] * b[i];
	return sum;
}

/** Computes the square of the magnitude of the given vector.
 */
double Sim::sqabs(vector<double> d)
{
	double dist = 0;
	for (int i = 0; i < d.size(); i++)
		dist += (d[i] * d[i]);
	return dist;	
}
