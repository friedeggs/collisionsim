#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "DataExporter.h"
#include "Ball.h"
#include "Sim.h"

using namespace std;

/** Monitors the specified Sim object and collects data 
 * that will be written to the specified output path in .csv format
 * when the write() method is called.
 */
DataExporter::DataExporter(string file_path, Sim &source)
{
	 // Init Variables
	 
	 filePath = file_path;
	 target = &source;
     
     coordNames.push_back('x');
     coordNames.push_back('y');
     coordNames.push_back('z');	 
}

/** Starts the data logging. Writes the column headers to the string buffer.
 */
void DataExporter::start()
{   
	// Ball label headers	    
    for (int i = 0; i < target->balls.size(); i++)
    	data << ",Ball " << i << ",,,";
	data << endl;
	
	// Constant parameters
	for (int i = 0; i < target->balls.size(); i++)
		data << ",m:," << target->balls[i].m << ",,";
	data << endl;
	
	for (int i = 0; i < target->balls.size(); i++)
		data << ",r:," << target->balls[i].r << ",,";
	data << endl;
	
	for (int i = 0; i < target->balls.size(); i++)
		data << ",k:," << target->balls[i].k << ",,";
	data << endl;
		
	// Variable headers
	
	data << "t,";
	
	for (int i = 0; i < target->balls.size(); i++)
	{	
		for (int j = 0; j < target->dim; j++)
			data << "s_" << coordNames[j] << ",";
		for (int j = 0; j < target->dim; j++)
			data << "v_" << coordNames[j] << ",";			
	}
	data << endl;
}

/** Writes one row of data in the specified output file; 
 * Logs the current position and velocity of all monitored balls
 * at the current time.
 */
void DataExporter::log()
{
	data << target->t << ",";
	
	// Log s and v
	
	for (int i = 0; i < target->balls.size(); i++)
	{
		for (int j = 0; j < target->dim; j++)
			data << target->balls[i].s[j] << ",";
		for (int j = 0; j < target->dim; j++)
			data << target->balls[i].v[j] << ",";
	}
	data << endl;
}

/** Exports the data collected so far to the file path
 * specified in the constructor for this class.
 *
 * @return true if the file was written successfully; false otherwise
 */
bool DataExporter::write()
{
    // these flags say:
     //    `out` - we will be writing data into the file
     //    `trunc` - if the file already exists, truncate (wipe out) the existing data

    ofstream fout(filePath.c_str(), ios_base::out | ios_base::trunc);

    // couldn't open it (disk error?); fail
    if (!fout.is_open())
    {    
    	cout << "Could not write to " << filePath << endl;
        return false;
    }

    fout.write(&(data.str()[0]), data.str().size());
    fout.close();

    cout << "Wrote " << data.str().size() << " bytes to " << filePath << endl;

    return true;
}