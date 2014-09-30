#ifndef SIM_H
#define SIM_H

#include <vector>
#include "Ball.h"

using namespace std;

class Sim
{
	public:
		Sim(int dimensions);
		void addBall(Ball ball);
		void advance(double dt);
		
		vector<Ball> balls;		
		double t;
		int dim;		
}
;

#endif // SIM_H
