#include <iostream>
#include "Ball.h"
#include "Sim.h"
#include "DataExporter.h"

/** TESTIINGGGGGGGGG!
	This is a test tooooooooo!
 */
int main()
{
	// Declaration of Variables
	
	Sim test(2);	
	Ball a(2);
	Ball b(2);
	DataExporter de("data.csv", test);
	
	// Add the two balls
	
	test.addBall(a);
	test.addBall(b);
	
	// Test: Advance sim by 10 steps and output data.
	
	cout << "Enter any key.";
	getchar();	
	de.start();
	
	for (int i = 0; i < 100; i++)
	{
		test.advance(0.1);
		de.log();
	}
	
	// Output csv
	
	de.write();
	
	return 0;
}
