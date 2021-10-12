
/*##############################################
############## E. COLI SIMULATION ##############
###############################################*/

#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <random>
#include "snm_functions.h"
#include "snm_variables.h"
#include "snm_tree.h"

using namespace std;

// Need to initalize arrays here because of "variable" length
unsigned long long int x[9];
double amu[17];
double amu_cumu[17];


int Simulation(string filename)
{

    SetUp(x);
    double nextStoptime = 0;
    double nextMovetime = move_dt;
	CreateTreeStructure();

	CalculateAmu(amu, amu_cumu, x, true);

	GeneratePutativeTimes(amu, amu_cumu, x);
	SortTree();
	Output(&nextStoptime, x, filename);
	nextStoptime += dt;
    while (currentTime < endTime) {
		//cout << glob_active_receptors[0] << " " << glob_active_receptors[1] << " ";
		//cout << glob_active_receptors[2] << " " << glob_active_receptors[3] << " ";
		//cout << glob_active_receptors[4] << endl;
		tau = tree_node_vec[0].tau;
		rIndex = tree_node_vec[0].reaction;
        while (tau > nextMovetime){
			if(runstate){
				Movement(move_dt);
			}
			if(nextMovetime >= nextStoptime){
				Output(&nextStoptime, x, filename);
				nextStoptime += dt;
			}
			nextMovetime += move_dt;
			if (nextMovetime > endTime){
				breaksim=1;
				break;
			}
			// no need for update and sort in every step, but this
			// happens very rarely, would need another if condition
			// to fix
			CalculateAmu(amu, amu_cumu, x, false);
			SortTree();
			tau = tree_node_vec[0].tau;
			rIndex = tree_node_vec[0].reaction;

		}
		if (breaksim){
			Output(&nextStoptime, x, filename);
			break;
		}

        Reactions(rIndex, x);
		currentTime = tau;
		CalculateAmu(amu, amu_cumu, x, false);
        SortTree();
    }
	//cout << "Number of reactions: " << reactions << endl;


    return 0;
}
