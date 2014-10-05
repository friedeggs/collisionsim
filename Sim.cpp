#include <vector>
#include <cstdlib>
#include <iterator> // std::distance
#include "Ball.h"
#include "Sim.h"

/** Constructs a simulation of the specified dimensions.
 */
Sim::Sim(int dimensions)
{
	dim = dimensions;
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
	for (int i = 0; i < balls.size() - 1; i++) {
		for (int j = i + 1; j < balls.size(); j++) {
			if (collision (balls[i], balls[j])) {
				tick_v(balls[i], balls [j], dt);
			}
		}
	}
	for (int i = 0; i < balls.size(); i++)
	{
		tick_s(balls[i], dt);
	}
	t += dt;
}

/** Advances the velocity vectors of the two balls 
 * as if they are in a collision.
 */
void Sim::tick_v(Ball &b1, Ball &b2, double dt)
{
	// The force constant is derived from Newton Law 3: F1 = F2.
	double force_const = b1.k * b2.k / (b1.k + b2.k);
	vector<double> strain(dim);
	vector<double> ds = b1.dist(b2);
	vector<double> relaxed_ds = b1.unstrained_r(b2);

	// Compute the compression
	
	for (int i = 0; i < dim; i++)	
		strain[i] = relaxed_ds[i] - ds[i];
		
	// Compute the spring accelerations and adjust v's accordingly
	
	for (int i = 0; i < dim; i++)
	{
		double force = strain[i] * force_const;
		b1.v[i] -= (force / b1.m) * dt;
		b2.v[i] += (force / b2.m) * dt;
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

/** Determines whether two balls are in contact
 *
 */
bool Sim::collision (Ball b1, Ball b2) {
	double dist = 0;
	for (int i = 0 ; i < dim ; i++)
		dist += (b1.s[i] - b2.s[i]) * (b1.s[i] - b2.s[i]);
	return dist <= (b1.r + b2.r) * (b1.r + b2.r);
}
