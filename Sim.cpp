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
	if (collision (balls[0], balls[1])) { // yo a collision is specific to two balls
		tick_s_a(balls[0], balls [1], dt);
	}
	for (int i = 0; i < balls.size(); i++)
	{
		tick_s(balls[i], dt);
	}
	t += dt;
}

/** Advances the position vector of the specified ball
 * as indicated by the ball's current velocity vector.
 */
void Sim::tick_s(Ball &ball, double dt)
{
	for (int i = 0; i < dim; i++)
		ball.s[i] += dt * ball.v[i];	
}

/** Advances the position vector of the specified ball
 * as indicated by the ball's current velocity vector
 * and acceleration vector
 */
void Sim::tick_s_a(Ball &b1, Ball &b2, double dt)
{
	/*
	compression calculations
	F1 = F2
	-k1 x1 = - k2 x2
	x1 + x2 = x
	-----------------
	x1 + k1 / k2 * x1 = x
	x1 (1 + k1 / k2 ) = x
	x1 (k1 + k2) / k2 = x
	-----------------
	x1 = x k2 / (k1 + k2)
	x2 = x k1 / (k1 + k2)
	*/
	double force_const = b1.k * b2.k / (b1.k + b2.k), x;
	for (int i = 0; i < dim; i++) {
		x = b1.r + b2.r - b1.s[i] - b2.s[i];
		if (x > 0) {
			b1.s[i] += dt * b1.v[i] - 0.5 * (x * force_const / b1.m) * dt * dt;
			b2.s[i] += dt * b2.v[i] - 0.5 * (x * force_const / b2.m) * dt * dt;
		}
	}
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
