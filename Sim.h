#ifndef SIM_H
#define SIM_H

#include <vector>
#include "Ball.h"

using namespace std;

class Sim
{
	public:
		Sim(int dimensions, bool rotation = false);	// Constructs a Simulation of the specified dimensions
		void addBall(Ball ball);					// Adds the specified ball to the simulation
		void advance(double dt);					// Advances the simulation using the laws of physics
		
		void tick_s(Ball &ball, double dt);			// Advances the ball's position based on its velocity
		void tick_v(Ball &b1, Ball &b2, double dt);	// Advances two colliding balls' velocities
		
		bool collision (Ball b1, Ball b2);			// Determines if two balls are in contact
		
		vector<Ball> balls;			// A list of all of the balls in this simulation
		double t;					// The current time
		double u_k;					// The coefficient of kinetic friction between objects
		int dim;					// The number of dimensions simulated
		bool rot;					// Rotation is simulated if true
}
;

#endif // SIM_H
