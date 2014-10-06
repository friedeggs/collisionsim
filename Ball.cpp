#include <vector>
#include <cstdlib>
#include <cmath>
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
		s.push_back(0);
		v.push_back(0);		
	}
	m = 1;
	r = 1;
	k = 1;
}

/** Computes the distance between this ball and 
 *  the specified ball. Returns a position vector
 *  pointing from this ball to the specified ball.
 */
vector<double> Ball::dist(Ball &ball)
{
	vector<double> ds;
	for (int i = 0; i < s.size(); i++)
		ds.push_back(ball.s[i] - s[i]);
	return ds;
}

/** Returns a position vector pointing to the specified ball.
 * The magnitude of the vector is equal to the sum of the radius
 * of this ball plus the radius of the specified ball.
 */
vector<double> Ball::unstrained_r(Ball &ball)
{
	vector<double> ds = dist(ball);
	double ds_magnitude = 0, scalar;
	
	// Compute the scalar req'd to obtain desired vector magnitude	
		
	for (int i = 0; i < ds.size(); i++)
		ds_magnitude += ds[i] * ds[i];
	ds_magnitude = sqrt(ds_magnitude);
	scalar = (r + ball.r) / ds_magnitude;
	
	// Apply the scalar to the relative position vector
	
	for (int i = 0; i < ds.size(); i++)
		ds[i] *= scalar;
		
	return ds;
}
