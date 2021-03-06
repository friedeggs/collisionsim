#ifndef SIM_H
#define SIM_H

#include <vector>
#include "Ball.h"

using namespace std;

class Sim
{
    public:
        Sim(int dimensions, bool rotation = false); // Constructs a Simulation of the specified dimensions
        void addBall(Ball ball); // Adds the specified ball to the simulation
        void advance(double dt); // Advances the simulation using the laws of physics
        
        void tick_s(Ball &ball, double dt); // Advances the ball's position based on its velocity
        void tick_v(Ball &b1, Ball &b2, double dt); // Advances the velocities of two colliding balls
        
        bool collision(Ball b1, Ball b2); // Determines if two balls are in contact
        double crossz(vector<double> a, vector<double> b); // Computes the z-component of the cross product
        double dot(vector<double> a, vector<double> b); // Computes the dot product
        double sqabs(vector<double> d); // Computes the square of the vector magnitude
        
        vector<Ball> balls; // A list of all of the balls in this simulation
        double t; // The current time
        double u_k; // The coefficient of kinetic friction between objects
        int dim; // The number of dimensions simulated
        bool rot; // Set true to effect rotational computations
}
;

#endif // SIM_H
