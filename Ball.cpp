#include <vector>
#include <cstdlib>
#include "Ball.h"

/** Initializes a Ball object of the specified dimensions.
 * Behaviour is undefined for dim < 0 and difficult for
 * humans to understand for dim > 3.
 *
 * For now, (change later), the ball's parameters are
 * initialized with random integer between 0 and 41.
 */
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
