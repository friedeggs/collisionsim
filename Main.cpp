#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "Ball.h"
#include "Sim.h"
#include "DataExporter.h"

using namespace std;

string inpath = "init.cfg";
string outpath = "data.csv";
double dt = 1;
double end_t = 1;
bool loaded = true;

/** A method that splits a string into an array of strings
 * based on the given delimiter. Used to aid input parsing.
 * Delimiter occurences are not included in the returned array.
 */
vector<string> split(string str, string delim)
{
	// Declare Variables
	
	vector<string> params;
	string temp;
	size_t right = str.find(delim);
	
	// Iterate through string, finding occurrences of the 
	// delimiter. Substring the segment to the array. Erase
	// the segment from the source string. Continue until 
	// there are no more delimiter occurrences.
	
	while (right != string::npos)
	{
		params.push_back(str.substr(0, right));
		str.erase(0, right + delim.size());
		right = str.find(delim);	
	}	
	params.push_back(str);	// Append the last remaining segment
	
	return params;
}

/** Reads the configuration settings and initial condition values
 * from file. Creates and returns a Sim object corresponding with
 * these parameters. Also updates the outpath, dt, and end_t global
 * varibles if specified. If no init file exists, returns a Sim of
 * dim = 0, and sets the global loaded bool to false.
 */
Sim loadInit()
{
	// Read File
	
	ifstream fin (inpath.c_str(), ios::in|ios::ate);
    if (fin.is_open())
    {       
        int size = fin.tellg();
        fin.seekg (0, ios::beg);
        vector<string>lines;    
		vector<string>params;    
        string line;
        while (getline(fin, line))        
        	lines.push_back(line);               
        fin.close();
        cout << "Successfully read " << inpath << ": " << size << " bytes" << endl;
        
        // Parse Simulation Configuration Data
        
        size_t left = 0, right = 0;
        double dim = 2;
        double u_k = 0;
        bool rotation = false;
        int i = 0;
        
        // Iterate through config file line by line
        
        do
        {
        	params = split(lines[i], " ");
        	
        	if (params[0] == "outpath")
        	{
        		params = split(lines[i], " ");
        		outpath = params[2].substr(1, params[2].size() - 2);
        	}
        	else if (params[0] == "dim")
        	{
        		dim = atoi(params[2].c_str());
        	}
        	else if (params[0] == "dt")
        	{
        		dt = atof(params[2].c_str());
        	}
        	else if (params[0] == "end_t")
        	{
        		end_t = atof(params[2].c_str());
        	}
        	else if (params[0] == "u_k")
        	{
        		u_k = atof(params[2].c_str());
        	}
        	else if (params[0] == "rotation")
        	{
	        	rotation = params[2] == "true";
        	}        
        }
        while (i++ < lines.size() && params.size() > 1);
        
        // Create Sim Object
        
        Sim sim(dim, rotation);
        sim.u_k = u_k;
        
        // Parse Ball Initial Condition Data
        
        while (i < lines.size())
        {     
        	params = split(lines[i], " ");
	        if (params[0] == "BALL")
	    	{
	    		Ball ball(dim);
	    		if (++i < lines.size())	    			    
					params = split(lines[i], " ");	
						
    			while (i < lines.size() && params.size() > 4) // Ball initial data are only stored in lines where n(params) > 4
    			{	    	
					// Read data
							  			
	    			if (params[2] == "s")	// Displacement data
	    			{        			
	    				for (int j = 0; j < dim; j++)
	    					ball.s[j] = atof(params[4 + j].c_str());
	    			}
	    			else if (params[2] == "v") // Velocity data
	    			{
	    				for (int j = 0; j < dim; j++)
	    					ball.v[j] = atof(params[4 + j].c_str());
	    			}
	    			else if (params[2] == "m") // Mass data
	    			{
	    			  	ball.m = atof(params[4].c_str());
	    			}
	    			else if (params[2] == "r") // Radius data
	    			{        			
	    				ball.r = atof(params[4].c_str());
	    			}
	    			else if (params[2] == "k") // Spring constant data
	    			{        			
	    				ball.k = atof(params[4].c_str());
	    			}    	
	    			
	    			// Prepare next line
	    			
	    			if (++i < lines.size())
						params = split(lines[i], " ");				   			
    			}
	    		
	    		sim.addBall(ball);	// Add ball to sim      	
	    	} 
	    	i++;
	    }        
        return sim;
    }
    else
    {
        cout << "Error: could not read " << inpath << endl;
        loaded = false;
        Sim sim(0, false);
        return sim;
    }
}

/** Writes a template initial conditions configuration file
 * to the specified file path.
 */
bool writeTemplateInit()
{
	// Declaration of Variables
	
	ofstream fout(inpath.c_str(), ios_base::out | ios_base::trunc);
	if (!fout.is_open())
		return false;
		
	// Write Template
	
	fout << "# === Configuration file for CollisionSim.exe ===" << endl;
	fout << "outpath = \"data.csv\"" << endl;
	fout << "dim = 2" << endl;
	fout << "dt = 0.001" << endl;
	fout << "end_t = 2.000" << endl;
	fout << "rotation = true" << endl;
	fout << "u_k = 0.5" << endl;
	fout << endl;
	fout << "# === Ball initial parameters ===" << endl;
	fout << "BALL 0" << endl;
	fout << "  s = 0 0" << endl;
	fout << "  v = 3 0" << endl;
	fout << "  m = 10" << endl;
	fout << "  r = 1" << endl;
	fout << "  k = 900" << endl;
	fout << endl;
	fout << "BALL 1" << endl;
	fout << "  s = 2.1 0" << endl;
	fout << "  v = 0 0" << endl;
	fout << "  m = 10" << endl;
	fout << "  r = 1" << endl;
	fout << "  k = 900" << endl;
	
	cout << "Finished creating " << inpath << endl;
    fout.close();
    
	return true;	
}

/** TESTIINGGGGGGGGG!
 */
int main()
{	
	// Initialize Variables
	
	Sim sim = loadInit();	
	DataExporter de(outpath, sim);
	
	// If init file missing, write template init file. Otherwise, simulate.
	
	if (!loaded)
	{	
		cout << "No valid init file exists. Will create a template init file." << endl;
		writeTemplateInit();
	}	
	else // Simulate
	{		
		de.start();	
		cout << endl << "Simulating..." << endl;
		while (sim.t < end_t)
		{
			sim.advance(dt);
			de.log();
		}	
		de.write();
	}
	
	return 0;
}
