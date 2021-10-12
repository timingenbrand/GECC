#include <iostream>
#include <math.h>
#include "snm_functions.h"
#include "snm_variables.h"
#include <random>


using namespace std;

void SetUp(unsigned long long int* x){

    // init values
    breaksim = 0;
    currentTime = 0;
    noutput = 0;
    reactions = 0;
    progress_count = 0;
    switchcount = 0;
    f = 6.0221415e17 * vol;
    Ttot = rec_fac* 5.3;
    amu_const2 = kR * CheR / (KR + Ttot);
    T0_init = (3.746 / 5.3) * Ttot;
    T1_init = (1.327 / 5.3) * Ttot;
    T2_init = (0.165 / 5.3) * Ttot;
    T3_init = (0.011 / 5.3) * Ttot;
    T4_init = (0 / 5.3) * Ttot;
    CheAp_init = (0.160 / 5.3) * CheAtot;
    CheYp_init = (2.700 / 9.7) * CheYtot;
    CheBp_init = (0.080 / 0.28) * CheBtot;

    //double min_posx_init = (2.5/30)*box_x;
    //double max_posx_init = (1/lambda)*log(1e3/grad_fac) + 2500;
	//posx_init = min_posx_init + (max_posx_init - min_posx_init) * (long double)mt_rand() / mt_rand.max();
    posx_init = (2.5/30) * box_x;
    posy_init = 0.5 * box_y;
    posx = posx_init;
    posy = posy_init;

    lig_conc = grad_fac;

    angle = 6.282 * (long double)mt_rand() / mt_rand.max();
    velx = v0 * cos(angle);   // init value
    vely = v0 * sin(angle);   // init value

	// setup all species
  	x[0] = (unsigned long long int)trunc(T0_init*f);  // T0 init
  	x[1] = (unsigned long long int)trunc(T1_init*f);  // T1 init
  	x[2] = (unsigned long long int)trunc(T2_init*f);  // T2 init
  	x[3] = (unsigned long long int)trunc(T3_init*f);  // T3 init
  	x[4] = (unsigned long long int)trunc(T4_init*f);  // T4 init
  	x[5] = (unsigned long long int)trunc(CheAp_init*f);  // CheA-P init
  	x[6] = (unsigned long long int)trunc(CheBp_init*f);  // CheB-P init
  	x[7] = (unsigned long long int)trunc(CheYp_init*f);  // CheY-P init
    x[8] = motors;

    return;
}

void Movement(double time){
    // only called if runstate == 1
    // Rotational Diffusion
    double std_dev = pow(Dr * time, 0.5);

    angle = genNormalDist(angle, std_dev); // adjust angle according to normal distribution, %(2pi)

    velx = v0 * cos(angle); // change velocity accordingly
    vely = v0 * sin(angle);


    // Propagate Cell
    posx += velx * time;
    posy += vely * time;
    if (posx > box_x) { breaksim = 1; } // stop run basically
    if (posx < 0) {
        velx *= -1;
        posx += velx * time;
        angle = atan(vely / velx);
    }
    if (posy > box_y || posy < 0) {
        vely *= -1;
        posy += vely * time;
        angle = atan(vely / velx);
    }
    lig_conc = grad_fac * exp(lambda * (posx - posx_init));  // gradient defined here
	/*
    lig_conc = (lambda * (posx-posx_init)) + grad_fac;
    if (lig_conc < 0) {
        lig_conc = 0;
    }
    */
    return;
}


void Reactions(int reaction_index, unsigned long long int* x) {
    reactions++;
    switch (reaction_index) {
        case 0:
            x[0]--;
            x[1]++;
            break;
        case 1:
            x[1]--;
            x[2]++;
            break;
        case 2:
            x[2]--;
            x[3]++;
            break;
        case 3:
            x[3]--;
            x[4]++;
            break;
        case 4:
            x[1]--;
            x[0]++;
            break;
        case 5:
            x[2]--;
            x[1]++;
            break;
        case 6:
            x[3]--;
            x[2]++;
            break;
        case 7:
            x[4]--;
            x[3]++;
            break;
        case 8:
            x[5]++;
            break;
        case 9:
            x[5]--;
            x[6]++;
            break;
        case 10:
            x[6]--;
            break;
        case 11:
            x[5]--;
            x[7]++;
            break;
        case 12:
            x[7]--;
            break;
        case 13:
            x[7]--;
            break;
        case 14:
            switchcount++;
            x[8]--;
            if (runstate == 1) {  // start tumbling
                runstate = 0;
                int dir = 1;

                if ((long double)mt_rand() / mt_rand.max() >0.5){
                  dir = -1;
                }

                // distribution for tumbling angle
                long double var = (long double)(mt_rand()+1.) / (mt_rand.max()+1.);
                double tumble_angle = 2*atan(sqrt( (1-var-sqrt(1-var)) / (var-1) ));
                angle += dir*tumble_angle;
                // re-calc velocities
                velx = v0 * cos(angle);
                vely = v0 * sin(angle);
            }
            break;
        case 15:
            switchcount++;
            x[8]++;
            if (x[8] == motors) { // start running
                runstate = 1;
            }
            break;
        cout << "\nError in updateSystem(): rIndex out of range:" << reaction_index ;
        exit(-1);
    }
    return;
}

void CalculateAmu(double* amu, unsigned long long int* x) {
    amu_const1 = pow(lig_conc, 1.2);

    //T_act0 = 0 * (1 - (amu_const1) / (amu_const1 + pow(2.7, 1.2))) * x[0] / f;
    T_act0 = 0;
    T_act1 = 0.25 * (1 - (amu_const1) / (amu_const1 + p20)) * x[1] / f;
    T_act2 = 0.5 * (1 - (amu_const1) / (amu_const1 + p150)) * x[2] / f;
    T_act3 = 0.75 * (1 - (amu_const1) / (amu_const1 + p1500)) * x[3] / f;
    T_act4 = 1 * (1 - (amu_const1) / (amu_const1 + p60000)) * x[4] / f;
    //T_act = T_act0 + T_act1 + T_act2 + T_act3 + T_act4;
    T_act = T_act1 + T_act2 + T_act3 + T_act4;

    amu_const3 = (x[6]* kB) / (KB + T_act);
    amu[0] = tau_factor*x[0] * amu_const2;
    amu[1] = tau_factor*x[1] * amu_const2 + amu[0];
    amu[2] = tau_factor*x[2] * amu_const2 + amu[1];
    amu[3] = tau_factor*x[3] * amu_const2 + amu[2];
    amu[4] = tau_factor*T_act1 * amu_const3 + amu[3];
    amu[5] = tau_factor*T_act2 * amu_const3 + amu[4];
    amu[6] = tau_factor*T_act3 * amu_const3 + amu[5];
    amu[7] = tau_factor*T_act4 * amu_const3 + amu[6];
    amu[8] = (kA * T_act * (CheAtot * f - x[5])) + amu[7];
    amu[9] = (kB_prime * (x[5] / f) * (CheBtot * f - x[6])) + amu[8];
    amu[10] = (gamB * x[6]) + amu[9];
    amu[11] = (kY * (x[5]/f) * (CheYtot * f - x[7])) + amu[10];
    amu[12] = (kZ * CheZ * x[7]) + amu[11];
    amu[13] = (gamY * x[7]) + amu[12];
    amu[14] = (x[8] / t0) * exp(-20 + (40 * (x[7] / f) / ((x[7] / f) + 3.06))) + amu[13];
    amu[15] = ((motors - x[8]) / t0) * exp(20 - (40 * (x[7] / f) / ((x[7] / f) + 3.06))) + amu[14];
    return;
}


// function to sample a normal distribution with mean mu and variance sig
double genNormalDist(double mu, double sig)
{

    long double v1 = (long double)(mt_rand()+1.) / (mt_rand.max()+1.);
    long double v2 = (long double)(mt_rand()+1.) / (mt_rand.max()+1.);
    double u1 = cos(2 * 3.141 * v2) * sqrt(-2. * log(v1));
    double var = u1 * (sig) + (mu);

    return(var);
}
