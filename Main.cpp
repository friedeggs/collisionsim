#include <iostream>
#include "Ball.h"
#include "Sim.h"
#include "DataExporter.h"

int main()
{
	Sim test(2);
	Ball a(2);
	Ball b(2);
	
	test.addBall(a);
	test.addBall(b);
	
	DataExporter de("data.csv", test);
	
	cout << "Ready?";
	getchar();
	
	de.start();
	
	for (int i = 0; i < 10; i++)
	{
		test.advance(1);
		de.log();
	}
	
	if (!de.write())
		cout << "FAIL";
	
	return 0;
}
