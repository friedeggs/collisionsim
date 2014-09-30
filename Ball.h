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
}
;

#endif // BALL_H
