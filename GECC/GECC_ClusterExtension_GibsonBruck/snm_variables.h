//#pragma once
#include <random>
extern int seed;
extern std::mt19937 mt_rand;

// List of global constants here
extern const int n_species;
extern const int n_reactions;
extern double tau_factor;
extern int runs;
extern double act_exp;
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
extern double move_dt;
extern int box_x;
extern int box_y;

extern double switchcount;

//extern double reaction_count[16];
extern int rIndex; // dummy value
extern int cIndex; // dummy value
extern int mIndex; // dummy value
extern double r1;  // dummy value
extern double r2;  // dummy value
extern double r3;  // dummy value
extern double r4;  // dummy value

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

extern int n_recep;
extern int cluster_no;
extern int cluster_size;
// cluster vectors
extern double activity_switchrate;
extern std::vector<std::vector<int>> clu_active_receptors;
extern std::vector<std::vector<int>> clu_inactive_receptors;
extern std::vector<int> glob_active_receptors;
extern std::vector<double> clu_active_percent;

extern std::vector<std::vector<double>> clu_switch_active_prop;
extern std::vector<std::vector<double>> clu_switch_inactive_prop;
extern std::vector<double> clu_switch_active_prop_msum;
extern std::vector<double> clu_switch_inactive_prop_msum;
extern std::vector<double> clu_switch_active_prop_msum_cumu;
extern std::vector<double> clu_switch_inactive_prop_msum_cumu;
extern std::vector<double> T_act_list;

extern std::vector<double> cumu_prop_meth;
extern std::vector<double> clu_receptor_m_cumu;

extern bool recalc_act_prop;
extern std::vector<int> recalc_list;
//extern int recalc_index;

extern int move_counter;
extern int prop_counter;

extern std::vector<double> putative_tau_list;
extern std::vector<int> tree_pointer_vec;
extern std::vector<int> curr_tree_order;

//extern struct Node;
