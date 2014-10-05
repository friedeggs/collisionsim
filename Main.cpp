#include <iostream>
#include "Ball.h"
#include "Sim.h"
#include "DataExporter.h"

/** TESTIINGGGGGGGGG!
 */
int main()
{
	// Declaration of Variables
	
	Sim test(2);	
	Ball a(2);
	Ball b(2);
	a.m=10;
	a.s[0]=0;
	a.s[1]=0;
	a.r=1;
	a.v[0]=3;
	a.v[1]=0;
	a.k = 900;
	
	b.m=10;
	b.s[0]=2.1;
	b.s[1]=0;
	b.r=1;
	b.v[0]=0;
	b.v[1]=0;
	b.k = 900;
	DataExporter de("data.csv", test);
	
	// Add the two balls
	
	test.addBall(a);
	test.addBall(b);
	
	// Test: Advance sim by 10 steps and output data.
	
	cout << "Enter any key.";
	getchar();	
	de.start();
	
	for (int i = 0; i < 2000; i++)
	{
		test.advance(0.001);
		de.log();
	}
	
	// Output csv
	
	de.write();
	
	return 0;
}
