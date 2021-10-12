#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include "snm_functions.h"
#include "snm_variables.h"
#include <random>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <Windows.h> // windows
using namespace std;

int main(int argc, char *argv[]) {
	// *** if running on cluster ***
    //int namecount = atoi(argv[1]);
    //int seed = atoi(argv[2]);
    //double input = atof(argv[3]);
    //lambda = input; // change inputas needed
	// ***
	int namecount = 0;
	int seed = 17;
	cout << seed << endl;
	mt_rand.seed(seed);
	cout << "\n##############################" << endl;
	cout << "##### Simulation started #####" << endl;
	cout << "##############################" << endl << endl;
	cout << "Number of cells: " << runs << endl;

	time_t starttime = time(nullptr);
	// need "runs" folder

    ostringstream folderObj;
	folderObj << "./runs/n";
	folderObj << runs;
	folderObj << "_t";
	folderObj << int(endTime);
	folderObj << "_lam";
	folderObj << lambda;
	folderObj << "_v";
	folderObj << vol*1e15;
	folderObj << "_tau";
	folderObj << tau_factor;
	folderObj << "_rec";
	folderObj << rec_fac;
	string folder = folderObj.str();


	// change according to operating system
	string folder_command = "mkdir " + folder;
	cout << folder << endl;
	char* cstr = &folder[0]; // windows/mac
	//char *cstr = &folder_command[0]; // cluster / linux
	//mkdir(cstr, 0777); // mac
	CreateDirectoryA(cstr,NULL); // windows
	//system(cstr); // cluster / linux


	// call Simulation with ("folder/name.csv")
	ParamOutput(folder+"/param.txt");
	WriteSeeds(folder+"/seeds.txt", namecount);
	for (int runrun = 0; runrun < runs; runrun++) {
		cout << "\nrun " << runrun << " ";
		Simulation(folder+"/bact" + to_string(runrun+namecount*runs) + ".csv");
	}




	time_t endtime = time(nullptr);

	cout << "\n##############################" << endl;
	cout << "##### Simulation finished ####" << endl;
	cout << "##############################" << endl << endl;
	cout << "Elapsed Time: " << endtime - starttime << "s" << endl;
	cout << "SpeedFactor: " << endTime*runs / float((endtime - starttime))  << endl;

	return 0;
}
