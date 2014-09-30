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
		
		vector<Ball> balls;			// A list of all of the balls in this simulation
		double t;					// The current time
		int dim;					// The number of dimensions simulated
}
;

#endif // SIM_H
