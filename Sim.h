#ifndef SIM_H
#define SIM_H

#include <vector>
#include "Ball.h"

using namespace std;

class Sim
{
	public:
		Sim(int dimensions);		// Constructs a Simulation of the specified dimensions
		void addBall(Ball ball);	// Adds the specified ball to the simulation
		void advance(double dt);	// Advances the simulation using the laws of physics
		
		void tick_s(Ball &ball, double dt);		// Advances the ball's position based on its velocity
		void tick_s_a(Ball &b1, Ball &b2, double dt);		// Advances the ball's position based on its velocity and acceleration
		
		bool collision (Ball b1, Ball b2);		// Determines if two balls are in contact
		
		vector<Ball> balls;			// A list of all of the balls in this simulation
		double t;					// The current time
		int dim;					// The number of dimensions simulated
}
;

#endif // SIM_H
