#include <iostream>
#include <math.h>
#include <random>
#include <time.h>
int runs = 1;
double endTime = 20;  // dummy value
double lambda = 0.005; // const value
double grad_fac = 0.01; // in mM
int seed = 0;
double tau_factor = 1;
double act_exp = 0;
std::mt19937 mt_rand(seed);

// Set values of global constants here
extern const int n_species = 9;
extern const int n_reactions = 17;

double vol = 1.4e-15;
double f = 6.0221415e17 * vol;
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
double Ttot = 5.3;
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

double T0_init = (3.746 / 5.3) * Ttot;
double T1_init = (1.327 / 5.3) * Ttot;
double T2_init = (0.165 / 5.3) * Ttot;
double T3_init = (0.011 / 5.3) * Ttot;
double T4_init = (0 / 5.3) * Ttot;
double CheAp_init = (0.160/5.3) *  CheAtot;
double CheYp_init = (2.700/9.7) * CheYtot;
double CheBp_init = (0.080/0.28) * CheBtot;


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

// List of input parameters here

double dt = 0.1;  // const value
double move_dt = 0.001; // const value
int box_x = 30000;  // dummy value
int box_y = 20000;  // dummy value

double switchcount = 0;

int rIndex = 0; // dummy value
int cIndex = 0; // dummy value
int mIndex = 0; // dummy value
double r1 = 0;  // dummy value
double r2 = 0;  // dummy value
double r3 = 0;  // dummy value
double r4 = 0;  // dummy value


// amu consts
double amu_const1 = 0; // dummy value
double amu_const2 = kR * CheR / (KR + Ttot);  // const value
double amu_const3 = 0;  // dummy value

double p20 = pow(0.02, 1.2); // in mM
double p150 = pow(0.15, 1.2);
double p1500 = pow(1.5, 1.2);
double p60000 = pow(60, 1.2);

int breaksim = 0;

int n_recep = 0; // dummy
int cluster_no = 0; // dummy
int cluster_size = 100; // parameter value, actually used unless overwritten
// cluster vectors
double activity_switchrate = 10;
std::vector<std::vector<int>> clu_active_receptors;
std::vector<std::vector<int>> clu_inactive_receptors;
std::vector<int> glob_active_receptors;
// could introduce glob_inactive_receptors, but its just
// glob_inactive_receptors[i] = x[i] - glob_active_receptors[i]

std::vector<double> clu_active_percent; //percentage
std::vector<std::vector<double>> clu_switch_active_prop; // count
std::vector<std::vector<double>> clu_switch_inactive_prop; // count
std::vector<double> clu_switch_active_prop_msum; // propensity
std::vector<double> clu_switch_inactive_prop_msum; // propensity
std::vector<double> clu_switch_active_prop_msum_cumu; // cumulative propensity
std::vector<double> clu_switch_inactive_prop_msum_cumu; // cumulative propensity


std::vector<double> T_act_list(5); // concentration

 // cumulative propensity, helping lists for sampling
std::vector<double> cumu_prop_meth(5);
std::vector<double> clu_receptor_m_cumu; // length = cluster_no

bool recalc_act_prop = true;
std::vector<int> recalc_list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
								12, 13, 14, 15, 16};
//int recalc_index = 0;
int move_counter = 0;
int prop_counter = 0;

std::vector<double> putative_tau_list(n_reactions, 0.);
std::vector<int> tree_pointer_vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
								12, 13, 14, 15, 16};
std::vector<int> curr_tree_order{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
									12, 13, 14, 15, 16};
