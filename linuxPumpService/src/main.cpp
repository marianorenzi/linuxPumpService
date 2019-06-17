#include <cstddef>
#include <cassert>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstdint>
#include <string.h>
#include <thread>
#include <unistd.h> 
#include <iostream>

// application
#include "pumpService/pumpService.h"

using namespace std;

int main(int argc, char* argv[])
{
	int opt;
	string configFile = "/etc/pumpService/pumpServiceConfig.json";
	string logFile = "/var/lib/pumpService/logs/pumpService.log";

	// put ':' in the starting of the 
	// string so that program can  
	//distinguish between '?' and ':'  
	while ((opt = getopt(argc, argv, "c:l:")) != -1)
	{
		switch (opt)
		{
		case 'c':
			configFile = string(optarg);
			break;
		case 'l':
			logFile = string(optarg);
			break; 
		case '?':
			if (optopt == 'c')
			{
				fprintf(stderr, "Invalid config file.\n");
			}
			else if (optopt == 'l')
			{
				fprintf(stderr, "Invalid log file.\n");
			}
			return 1;
		}
	}

	cout << "config file path: " << configFile << endl;
	cout << "log file path: " << logFile << endl;

	// create pump service
	PumpService *pumpService = new PumpService(configFile, logFile);

	// join service
	pumpService->join();

	return 0;
}