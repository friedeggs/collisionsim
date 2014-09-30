#include <vector>
#include <cstdlib>
#include "Ball.h"

Ball::Ball(int dim)
{
	for (int i = 0; i < dim; i++)
	{
		s.push_back(rand()%42);
		v.push_back(rand()%42);
		m = rand()%42;
		r = rand()%42;
		k = rand()%42;
	}
}
