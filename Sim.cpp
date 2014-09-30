#include <vector>
#include <cstdlib>
#include "Ball.h"
#include "Sim.h"

int dim;
double t;
vector <Ball> balls;

Sim::Sim(int dimensions)
{
	dim = dimensions;
	t = 0;
}

void Sim::addBall(Ball ball)
{
	balls.push_back(ball);
}

void Sim::advance(double dt)
{
	// BLEARRRRRRRRRRRRRGH
	
	for (int i = 0; i < balls.size(); i++)
	{
		for (int j = 0; j < dim; j++)
		{
			balls[i].s[j] = rand() % 42;
			balls[i].v[j] = rand() % 42;
		}
	}
	t += dt;
}
