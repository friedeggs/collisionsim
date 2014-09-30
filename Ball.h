#ifndef BALL_H
#define BALL_H

#include <vector>

using namespace std;

class Ball
{
	public:
		Ball(int dim);
		vector<double> s;
		vector<double> v;
		double m;
		double r;
		double k;
}
;

#endif // BALL_H
