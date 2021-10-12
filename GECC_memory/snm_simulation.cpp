
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



using namespace std;

// Need to initalize arrays here because of "variable" length
unsigned long long int x[9]; // species
double amu[16]; // propensities



int Simulation(string filename)
{
	bool increased = false;
    SetUp(x);

    double nextStoptime = dt;

	// start of main loop
    while (currentTime < endTime) {
		if (!increased){
			if (currentTime > 100){
				r1 = (long double)(mt_rand()+1.)/(mt_rand.max()+1.);
				lig_conc = 0.01 + 0.02*r1;
				increased = true;
			}
		}
        CalculateAmu(amu, x); // calc propensities

        r1 = (long double)(mt_rand()+1.)/(mt_rand.max()+1.);
        tau = -log(r1) / amu[n_reactions - 1]; // generate new tau

        while(tau>dt){ // does tau jump over the next save-time?
		  	if (!increased){
				if (currentTime > 100){
					r1 = (long double)(mt_rand()+1.)/(mt_rand.max()+1.);
					lig_conc = 0.01 + 0.02*r1;
					increased = true;
				}
		  	}
          //Movement(dt);
          Output(&nextStoptime, x, filename);
          nextStoptime += dt;
          currentTime += dt;

          if (currentTime > endTime) {
			  //cout << "Break here" << endl;
              breaksim = true;
              break;
            }
          CalculateAmu(amu, x); // re-calc propensities after movement

          r1 = (long double)(mt_rand()+1.)/(mt_rand.max()+1.);
          tau = -log(r1) / amu[n_reactions - 1]; // re-generate tau
        }
        if (breaksim) {
            break;
        }
        currentTime += tau;

        if (runstate){ // do remaining movement
            //Movement(tau);
        }

        // determine which reaction is happening
        r2 = amu[n_reactions - 1] *(long double)(mt_rand()+1.)/(mt_rand.max()+1.);
        for (rIndex = 0; amu[rIndex] < r2; rIndex++);

		// execute reaction
        Reactions(rIndex, x);

		// save data
        if (currentTime > nextStoptime) {
            Output(&nextStoptime, x, filename);
            nextStoptime += dt;
        }

    }
    return 0;
}
