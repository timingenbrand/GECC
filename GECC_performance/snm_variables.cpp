#include <iostream>
#include <math.h>
#include <random>
#include <time.h>
int runs = 100;
double endTime = 500;
double lambda = 0.005; // const value
double grad_fac = 0.01; // in mM
double rec_fac = 1;
int seed = 0;
double tau_factor = 1;

std::mt19937 mt_rand(seed);

// Set values of global constants here
extern const int n_species = 9;
extern const int n_reactions = 16;

double vol = 1.4e-15;
double f = 0;
double v0 = 11.82;  // in �m/s
double kA = 50;
double kB_prime = 3;
double gamB = 1;
double kY = 100; // 100 in Kollmann paper! 45.05 in Vladimirov 2008
double kZ = 30;
double gamY = 0.1;
double kR = 0.39;
double KR = 0.099;
double kB = 6.3;
double KB = 2.5;

double CheR = 0.16;
double CheZ = 1;
double Ttot = 0; //in setup
double CheAtot = 5.3;
double CheBtot = 0.28;
double CheYtot = 7.9;

// Navigation variables
double t0 = 0.77;  // const value
int motors = 3;    // const value
double Dr = 0.062; //  rad/s, const value
int runstate = 1;  // init value, 1 = run, 0 = tumble
double angle = 6.282 * ((double)mt_rand() / mt_rand.max()); // init value



double velx = 0;  // init value
double vely = 0;  // init value
double posx = 0;  // dummy value
double posy = 0;  // dummy value
double posx_init = 0; // dummy value
double posy_init = 0; // dummy value


double T0_init = 0;
double T1_init = 0;
double T2_init = 0;
double T3_init = 0;
double T4_init = 0;
double CheAp_init = 0;
double CheBp_init = 0;
double CheYp_init = 0;

double lig_conc = 0; // dummy value
double T_act = 0;   // dummy value
double T_act0 = 0;  // dummy value
double T_act1 = 0;  // dummy value
double T_act2 = 0;  // dummy value
double T_act3 = 0;  // dummy value
double T_act4 = 0;  // dummy value


double currentTime = 0;  // init value
double tau = 0;  // dummy value
double new_tau = 0;

int noutput = 0;  // init value
int reactions = 0;  // init value
double progress[10] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
int progress_count = 0;  // init value

// List of input parameters here

double dt = 0.1;  // dummy value
int box_x = 30000;  // dummy value
int box_y = 20000;  // dummy value

double switchcount = 0;

int rIndex = 0; // dummy value
double r1 = 0;  // dummy value
double r2 = 0;  // dummy value




// amu consts
double amu_const1 = 0; // dummy value
//double amu_const2 = kR * CheR / (KR + Ttot);  // const value
double amu_const2 = 0;
double amu_const3 = 0;  // dummy value

double p20 = pow(0.02, 1.2); // in mM
double p150 = pow(0.15, 1.2);
double p1500 = pow(1.5, 1.2);
double p60000 = pow(60, 1.2);

int breaksim = 0;

// tumbling angle
double poly_param[8] = {3.08103327e-02,  9.96341785e+00, -9.67590975e+01,  5.38580916e+02,
 -1.54391203e+03,  2.33821142e+03, -1.77722717e+03,  5.33955671e+02};
