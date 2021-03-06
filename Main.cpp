#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "Ball.h"
#include "DataExporter.h"
#include "Sim.h"

using namespace std;

string inpath = "init.cfg";
string outpath = "data.csv";
double dt = 1;
double end_t = 1;
bool loaded = true;

/** Splits a string into a string array using the given delimiter.
 * Used to aid input parsing. Delimiter occurences are not included
 * in the returned array.
 */
vector<string> split(string str, string delim)
{
    // Declare Variables
    
    vector<string> params;
    string temp;
    size_t right = str.find(delim);
    
    // Iterate through string, finding occurrences of delimiter. 
    // Substring segment to array. Erase segment from source
    // string. Continue until no more delimiter occurrences.
    
    while (right != string::npos)
    {
        params.push_back(str.substr(0, right));
        str.erase(0, right + delim.size());
        right = str.find(delim);    
    }    
    params.push_back(str);    // Append the last remaining segment
    
    return params;
}

/** Reads the configuration settings and initial condition values
 * from file. Creates and returns a Sim object corresponding with
 * these parameters. Also sets the outpath, dt, and end_t global
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
        //cout << "Successfully read " << inpath << ": " << size << " bytes" << endl;
        
        // Parse Simulation Configuration Data
        
        double dim = 2;
        double u_k = 0;
        bool rotation = false;
        int i = 0;
        
        // Iterate through config file line by line
        
        do
        {
            params = split(lines[i], " ");
            
            if (params[0] == "outpath")            
                outpath = params[2].substr(1, params[2].size() - 2);
            
            else if (params[0] == "dim")            
                dim = atoi(params[2].c_str());
            
            else if (params[0] == "dt")            
                dt = atof(params[2].c_str());
            
            else if (params[0] == "end_t")            
                end_t = atof(params[2].c_str());
            
            else if (params[0] == "u_k")
                u_k = atof(params[2].c_str());
            
            else if (params[0] == "rotation")
                rotation = params[2] == "true";
        }
        while (++i < lines.size() && params.size() > 1);
        
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
                        
                // Ball initial data are only stored in lines where n(params) > 4
                while (i < lines.size() && params.size() > 4) 
                {            
                    // Read data
                                          
                    if (params[2] == "s")    // Displacement data                                       
                        for (int j = 0; j < dim; j++)
                            ball.s[j] = atof(params[4 + j].c_str());
                    
                    else if (params[2] == "v") // Velocity data                    
                        for (int j = 0; j < dim; j++)
                            ball.v[j] = atof(params[4 + j].c_str());
                    
                    else if (params[2] == "m") // Mass data                    
                          ball.m = atof(params[4].c_str());
                    
                    else if (params[2] == "r") // Radius data                                      
                        ball.r = atof(params[4].c_str());
                    
                    else if (params[2] == "k") // Spring constant data                                   
                        ball.k = atof(params[4].c_str());
                     
                    else if (params[2] == "w") // Spring constant data                          
                        ball.w = atof(params[4].c_str());
                                        
                    // Prepare next line
                    
                    if (++i < lines.size())
                        params = split(lines[i], " ");                               
                }
                
                // Recompute I in case m or r changed
                
                ball.I = 0.4 * ball.m * ball.r * ball.r;
                sim.addBall(ball);    // Add ball to sim          
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
 * to the inpath.
 */
bool writeTemplateInit()
{
    ofstream fout(inpath.c_str(), ios_base::out | ios_base::trunc);
    if (!fout.is_open())
        return false;
        
    // Write Template
    
    fout << "# === Configuration file for CollisionSim.exe ===" << endl;
    fout << "outpath = \"data.csv\"" << endl;
    fout << "dim = 2" << endl;
    fout << "dt = 0.0001" << endl;
    fout << "end_t = 0.15" << endl;
    fout << "rotation = true" << endl;
    fout << "u_k = 0.5" << endl;
    fout << endl;
    fout << "# === Ball initial parameters ===" << endl;
    fout << "BALL 0" << endl;
    fout << "  s = 0 0" << endl;
    fout << "  v = 5 0" << endl;
    fout << "  m = 0.032" << endl;
    fout << "  r = 0.068" << endl;
    fout << "  k = 980" << endl;
    fout << "  w = 0" << endl;
    fout << endl;
    fout << "BALL 1" << endl;
    fout << "  s = 0.21 0" << endl;
    fout << "  v = 0 0" << endl;
    fout << "  m = 0.032" << endl;
    fout << "  r = 0.068" << endl;
    fout << "  k = 980" << endl;
    fout << "  w = 0" << endl;    
    
    cout << "Finished creating " << inpath << endl;
    fout.close();
    
    return true;    
}

/** Runs the simulation with different starting positions for
 * ball 2, printing the final velocity angles of each ball for
 * each iteration. Used to find a set of initial conditions
 * corresponding with those stipulated in a sample problem.
 */
void bruteForceAngles(int coord, double start, double step, int n)
{
    for (int i = 0; i < n; i++)
    {
        Sim sim = loadInit();
        sim.balls[1].s[coord] = start + i * step;
        while (sim.t < end_t)
            sim.advance(dt);
        cout << "b2.s[" << coord <<"] " << start + i * step << " ; theta 1 =  " << 180 / M_PI * atan(sim.balls[0].v[1] / sim.balls[0].v[0]);
        cout << " theta 2 = " << 180 / M_PI * atan(sim.balls[1].v[1] / sim.balls[1].v[0]) << endl;        
    }
    
}

int main()
{        
    // Initialize Variables
    
    Sim sim = loadInit();    
    DataExporter de(outpath, sim);
    
    // If init file missing, write template init file. Otherwise, simulate.
    
    if (!loaded)
    {    
        cout << "No valid init file exists. Creating template init file..." << endl;
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
