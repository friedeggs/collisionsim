#include <vector>
#include <cstdlib>
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
