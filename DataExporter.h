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
		DataExporter(string file_path, Sim &source);	
		void start();
		void log();
		bool write();
		
		Sim *target;
		string filePath;
		ostringstream data;
		//vector<char> data;
		vector<char> coordNames;		
}
;

#endif // DATAEXPORTER_H


