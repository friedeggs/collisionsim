#ifndef BALL_H
#define BALL_H

#include <vector>

using namespace std;

class Ball
{
    public:
        Ball(int dim);    // Constructs a ball in dim dimensions
        
        vector<double> s;        // The position vector
        vector<double> v;        // The velocity vector
        double m;                // The mass
        double r;                // The radius (ball is spherical)
        double k;                // The spring constant
        double theta;            // The angular displacement
        double w;                // The angular velocity
        double I;                // The rotational inertia
        
        vector<double> dist(Ball &ball); // Returns the distance to ball
        vector<double> unstrained_r(Ball &ball); // Returns relaxed distance to ball
}
;

#endif // BALL_H
