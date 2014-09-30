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
 *
 * Though right now it just assigns a random int for
 * every position and velocity component to every ball
 * in the situation. :P
 */
void Sim::advance(double dt)
{
	// RANDOMMMMM
	
	for (int i = 0; i < balls.size(); i++)
	{
		for (int j = 0; j < dim; j++)
		{
			balls[i].s[j] = rand() % 42;
			balls[i].v[j] = rand() % 42;
		}
	}
	t += dt;
}
