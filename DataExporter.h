#ifndef DATAEXPORTER_H
#define DATAEXPORTER_H

#include <vector>
#include <sstream>
#include <fstream>
#include "Ball.h"
#include "Sim.h"

using namespace std;

class DataExporter
{
	public:
		DataExporter(string file_path, Sim &source);	// Constructs a DataExporter	
		void start();			// Initializes the output buffer with column headers etc.
		void log();				// Records a snapshot of the current situation
		bool write();			// Exports output buffer to file
		
		Sim *target;			// The Sim object that this DataExporter is monitoring
		string filePath;		// The target file path for the output file
		ostringstream data;		// The string stream used as an output buffer
		vector<char> coordNames; 	// Associates a dimension component index (e.g. 0,1,2) to its
									// corresponding name (e.g. x,y,z).
}
;

#endif // DATAEXPORTER_H


