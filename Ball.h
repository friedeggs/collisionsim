#ifndef BALL_H
#define BALL_H

#include <vector>

using namespace std;

class Ball
{
	public:
		Ball(int dim);			// Constructs a ball in dim dimensions
		vector<double> s;		// The position vector
		vector<double> v;		// The velocity vector
		double m;				// The mass
		double r;				// The radius (Ball is spherical)
		double k;				// The spring constant
		
		vector<double> dist(Ball &ball); // Returns the relative s vector to ball
		vector<double> unstrained_r(Ball &ball); // Returns a relative s vector to ball
}
;

#endif // BALL_H
