//#pragma once
#include <random>
extern int seed;
extern std::mt19937 mt_rand;

// List of global constants here
extern const int n_species;
extern const int n_reactions;
extern double tau_factor;
extern double rec_fac;
extern int runs;

extern double vol;
extern double f;
extern double v0;  // in �m/s
extern double kA;
extern double kB_prime;
extern double gamB;
extern double kY;
extern double kZ;
extern double gamY;
extern double kR;
extern double KR;
extern double kB;
extern double KB;


extern double CheR;
extern double CheZ;
extern double Ttot;
extern double CheAtot;
extern double CheBtot;
extern double CheYtot;

//Navigation variables
extern double t0;
extern int motors;
extern double Dr;
extern int runstate;
extern double posx;
extern double posy;
extern double posx_init;
extern double posy_init;
extern double velx;
extern double vely;
extern double angle;


extern double T0_init;
extern double T1_init;
extern double T2_init;
extern double T3_init;
extern double T4_init;
extern double CheAp_init;
extern double CheBp_init;
extern double CheYp_init;



extern double grad_fac;
extern double lig_conc;
extern double T_act;
extern double T_act0;
extern double T_act1;
extern double T_act2;
extern double T_act3;
extern double T_act4;

extern double currentTime;
extern double tau;
extern double new_tau;
extern int noutput;
extern int reactions; // number of reactions during sim
extern double progress[10];
extern int progress_count;


// List of input parameters here
extern double endTime;
extern double dt;
extern int box_x;
extern int box_y;

extern double switchcount;

//extern double reaction_count[16];
extern int rIndex; // dummy value
extern double r1;  // dummy value
extern double r2;  // dummy value

// gradient params
extern double lambda;

// amu consts
extern double amu_const1;
extern double amu_const2;
extern double amu_const3;
extern double p20;
extern double p150;
extern double p1500;
extern double p60000;


extern int breaksim;

extern double poly_param[8];
