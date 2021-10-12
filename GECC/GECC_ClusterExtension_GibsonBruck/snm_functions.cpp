#include <iostream>
#include <math.h>
#include "snm_functions.h"
#include "snm_variables.h"
#include "snm_tree.h"
#include <random>
#include <numeric>


using namespace std;

void SetUp(unsigned long long int* x){
    // init values
    breaksim = 0;
    currentTime = 0;
    noutput = 0;
    reactions = 0;
    switchcount = 0;
	runstate=1;
	recalc_list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
									12, 13, 14, 15, 16};
	recalc_act_prop = true;
	tree_pointer_vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
		 							12, 13, 14, 15, 16};
    //double min_posx_init = (2.5/30)*box_x;
    //double max_posx_init = (1/lambda)*log(1e3/grad_fac) + 2500;
	//posx = min_posx_init + (max_posx_init - min_posx_init) * (long double)mt_rand() / mt_rand.max();

    posx_init = (2.5/30) * box_x;
    posy_init = 0.5 * box_y;
    posx = posx_init;
    posy = posy_init;
    lig_conc = grad_fac;
    //angle = 6.282 * (float)(int(rand()) + 1) / (RAND_MAX);  // init value
    angle = 6.282 * (long double)mt_rand() / mt_rand.max();
    velx = v0 * cos(angle);   // init value
    vely = v0 * sin(angle);   // init value

  	x[0] = (unsigned long long int)trunc(T0_init*f);  // T0 init
  	x[1] = (unsigned long long int)trunc(T1_init*f);  // T1 init
  	x[2] = (unsigned long long int)trunc(T2_init*f);  // T2 init
  	x[3] = (unsigned long long int)trunc(T3_init*f);  // T3 init
  	x[4] = (unsigned long long int)trunc(T4_init*f);  // T4 init
  	x[5] = (unsigned long long int)trunc(CheAp_init*f);  // CheA-P init
  	x[6] = (unsigned long long int)trunc(CheBp_init*f);  // CheB-P init
  	x[7] = (unsigned long long int)trunc(CheYp_init*f);  // CheY-P init
    x[8] = motors;


	// put all receptors into one cluster because we dont want to look at clusters
	// cluster influence is disabled anyway by setting act_exp = 0
	// this speeds up simulation significantly compared to smaller cluster_size
	cluster_size = x[0] + x[1] + x[2] + x[3] + x[4];
	CreateClusters(x);

    return;
}

void Movement(double time){
	recalc_act_prop = true;
	recalc_list = {15, 16};
    // only called if runstate == 1
    // Rotational Diffusion
    double std_dev = pow(Dr * time, 0.5);

    angle = genNormalDist(angle, std_dev); // adjust angle according to normal distribution, %(2pi)

    velx = v0 * cos(angle); // change velocity accordingly
    vely = v0 * sin(angle);


    // Propagate Cell
	//cout << "velx " << velx << " time " << time << " displacex "<< velx*time << endl;
    posx += velx * time;
    posy += vely * time;
    if (posx > box_x) {
		breaksim = 1;
	} // stop run basically
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
	return;
}


void Reactions(int reaction_index, unsigned long long int* x) {
    reactions++;
    switch (reaction_index) {
        case 0:
			//methylation event, need sampling!
			SampleMethylation(0);
            x[0]--;
            x[1]++;
			recalc_act_prop = true; // could be optimized to only re-calc one cluster
			recalc_list = {0, 1, 4, 8, 15, 16};
            break;
        case 1:
			SampleMethylation(1);
            x[1]--;
            x[2]++;
			recalc_act_prop = true; // could be optimized to only re-calc one cluster
			recalc_list = {1, 2, 4, 5, 8, 15, 16};
            break;
        case 2:
			SampleMethylation(2);
            x[2]--;
            x[3]++;
			recalc_act_prop = true; // could be optimized to only re-calc one cluster
			recalc_list = {2, 3, 5, 6, 8, 15, 16};
            break;
        case 3:
			SampleMethylation(3);
            x[3]--;
            x[4]++;
			recalc_act_prop = true; // could be optimized to only re-calc one cluster
			recalc_list = {3, 6, 7, 8, 15, 16};
            break;
        case 4:
			SampleDemethylation(1);
            x[1]--;
            x[0]++;
			recalc_act_prop = true; // could be optimized to only re-calc one cluster
			recalc_list = {0, 1, 4, 8, 15, 16};
            break;
        case 5:
			SampleDemethylation(2);
            x[2]--;
            x[1]++;
			recalc_act_prop = true; // could be optimized to only re-calc one cluster
			recalc_list = {1, 2, 4, 5, 8, 15, 16};
            break;
        case 6:
			SampleDemethylation(3);
            x[3]--;
            x[2]++;
			recalc_act_prop = true; // could be optimized to only re-calc one cluster
			recalc_list = {2, 3, 5, 6, 8, 15, 16};
            break;
        case 7:
			SampleDemethylation(4);
            x[4]--;
            x[3]++;
			recalc_act_prop = true; // could be optimized to only re-calc one cluster
			recalc_list = {3, 6, 7, 8, 15, 16};
            break;
        case 8:
            x[5]++;
			recalc_list = {8, 9, 11};
            break;
        case 9:
            x[5]--;
            x[6]++;
			recalc_list = {4, 5, 6, 7, 8, 9, 10, 11};
            break;
        case 10:
            x[6]--;
			recalc_list = {9, 10};
            break;
        case 11:
            x[5]--;
            x[7]++;
			recalc_list = {8, 9, 11, 12, 13, 14};
            break;
        case 12:
            x[7]--;
			recalc_list = {11, 12, 13, 14};
            break;
        case 13:
            switchcount++;
            x[8]--;
            if (runstate == 1) {  // start tumbling
                runstate = 0;
				//cout << "tumble at time " << currentTime << endl;
                int dir = 1;

                if ((long double)mt_rand() / mt_rand.max() >0.5){
                  dir = -1;
                }

                // distribution for tumbling angle
                long double r3 = (long double)mt_rand() / (mt_rand.max()+1.);
                double tumble_angle = 2*atan(sqrt( (1-r3-sqrt(1-r3)) / (r3-1) ));
                angle += dir*tumble_angle;
                // re-calc velocities
                velx = v0 * cos(angle);
                vely = v0 * sin(angle);
            }
			recalc_list = {13, 14};
            break;
        case 14:
            switchcount++;
            x[8]++;
            if (x[8] == motors) { // start running
                runstate = 1;
				//cout << "runstart at time " << currentTime << endl;
            }
			recalc_list = {13, 14};
            break;
		case 15:
			// receptor activation, first sample for which cluster cIndex
			r3 = clu_switch_active_prop_msum_cumu[cluster_no - 1]*
				(long double)(mt_rand()+1.) / (mt_rand.max()+1.);
			for (cIndex = 0; clu_switch_active_prop_msum_cumu[cIndex] < r3; cIndex++);
			//cout <<"Activated Cluster "<<cIndex<<endl;
			// second: sample for which methylation level mIndex
			partial_sum(clu_switch_active_prop[cIndex].begin(),
				clu_switch_active_prop[cIndex].end(), cumu_prop_meth.begin());
			r3 = cumu_prop_meth[5 - 1]*(long double)(mt_rand()+1.) / (mt_rand.max()+1.);
			for (mIndex = 0; cumu_prop_meth[mIndex] < r3; mIndex++);
			// update all relevant vectors
			clu_active_receptors[cIndex][mIndex]++;
			clu_inactive_receptors[cIndex][mIndex]--;
			glob_active_receptors[mIndex]++;
			clu_active_percent[cIndex] = (((clu_active_percent[cIndex]*
				cluster_size)+1) / cluster_size);
			//cout << "a cIndex" << cIndex << " mIndex" << mIndex << " clu_active_percent"<< clu_active_percent[cIndex] << endl;

			recalc_list = {4, 5, 6, 7, 8, 15, 16};
			recalc_act_prop = true;
			break;
		case 16:

			// receptor DEactivation, first sample for which cluster
			r3 = clu_switch_inactive_prop_msum_cumu[cluster_no - 1]*
				(long double)(mt_rand()+1.) / (mt_rand.max()+1.);
			for (cIndex = 0; clu_switch_inactive_prop_msum_cumu[cIndex] < r3; cIndex++);
			//cout <<"DeActivated Cluster "<<cIndex<<endl;
			// second: sample for which methylation level
			partial_sum(clu_switch_inactive_prop[cIndex].begin(),
				clu_switch_inactive_prop[cIndex].end(), cumu_prop_meth.begin());
			r3 = cumu_prop_meth[5 - 1]*(long double)(mt_rand()+1.) / (mt_rand.max()+1.);
			for (mIndex = 0; cumu_prop_meth[mIndex] < r3; mIndex++);

			// update all relevant vectors

			clu_active_receptors[cIndex][mIndex]--;
			clu_inactive_receptors[cIndex][mIndex]++;
			glob_active_receptors[mIndex]--;
			clu_active_percent[cIndex] = (((clu_active_percent[cIndex]*
				cluster_size)-1) / cluster_size);
			//cout << "i cIndex" << cIndex << " mIndex" << mIndex << " clu_active_percent"<< clu_active_percent[cIndex] << endl;

			recalc_list = {4, 5, 6, 7, 8, 15, 16};
			recalc_act_prop = true;
            break;
        cout << "\nError in updateSystem(): rIndex out of range:" << reaction_index ;
        exit(-1);

    }
    return;
}



void CalculateAmu(double* amu, double* amu_cumu, unsigned long long int* x, bool start) {
    amu_const1 = pow(lig_conc, 1.2);
	amu_const3 = (x[6]* kB) / (KB + T_act);

	if (recalc_act_prop){
		CalcActivationProp(x, amu);
		// T_act is concentration of active receptors summed over all clusters
		// and methylation levels
		T_act = 0.;
		for (int mm = 0; mm<5; mm++){
			T_act_list[mm] = glob_active_receptors[mm] / f;
			T_act += T_act_list[mm];
		}
	}

	// update necessary propensities
	for(int recalc_index : recalc_list){
		UpdateAmu(recalc_index, amu, x, start);
	}
	if (tree_node_vec[tree_pointer_vec[11]].tau < 0) {
		cout << "break" << endl;
	}

	// sum up amu for amu_cumu, maybe not needed with GibsonBruck
	amu_cumu[0] = amu[0];
	for (int cc=1; cc<n_reactions; cc++){
		amu_cumu[cc] = amu_cumu[cc-1] + amu[cc];
	}

    return;
}

void CalcActivationProp(unsigned long long int* x, double* amu){
	prop_counter++;
	recalc_act_prop = false;
	// in general: prop_act = omega * inact_rec * p_act
	vector<double> active_probability(5, 0.);
	double theta;
	int mm;
	for (int pp=0; pp<cluster_no; pp++){
		theta = pow((1.5 - clu_active_percent[pp]), act_exp);
		// meth level 0
		active_probability[0] = 0;
		active_probability[1] = 0.25 * (1-((theta*amu_const1) /
		 	((theta*amu_const1)+p20)));
		active_probability[2] = 0.50 * (1-((theta*amu_const1) /
		 	((theta*amu_const1)+p150)));
		active_probability[3] = 0.75 * (1-((theta*amu_const1) /
			((theta*amu_const1)+p1500)));
		active_probability[4] = 1.00 * (1-((theta*amu_const1) /
			((theta*amu_const1)+p60000)));

		clu_switch_active_prop_msum[pp] = 0;
		clu_switch_inactive_prop_msum[pp] = 0;
		for(mm=0; mm<5; mm++){
			clu_switch_active_prop[pp][mm] = active_probability[mm] *
					clu_inactive_receptors[pp][mm] * activity_switchrate;
			clu_switch_inactive_prop[pp][mm] = (1-active_probability[mm]) *
					clu_active_receptors[pp][mm] * activity_switchrate;

			clu_switch_active_prop_msum[pp] += clu_switch_active_prop[pp][mm];
			clu_switch_inactive_prop_msum[pp] += clu_switch_inactive_prop[pp][mm];
		}

	}

	// calculate over all clusters cumulative vector of propensities
	// for later sampling
	partial_sum(clu_switch_active_prop_msum.begin(), clu_switch_active_prop_msum.end(),
		clu_switch_active_prop_msum_cumu.begin());
	partial_sum(clu_switch_inactive_prop_msum.begin(), clu_switch_inactive_prop_msum.end(),
			clu_switch_inactive_prop_msum_cumu.begin());
	return;
}

void SampleMethylation(int level){

	// methylation process
	// which cluster
	// calculate cumulative receptor distribution over clusters
	clu_receptor_m_cumu[0] = clu_active_receptors[0][level] +
		clu_inactive_receptors[0][level];
	for(int cc=1; cc<cluster_no; cc++){
		clu_receptor_m_cumu[cc] = clu_active_receptors[cc][level] +
			clu_inactive_receptors[cc][level] + clu_receptor_m_cumu[cc-1];
	}

	r3 = clu_receptor_m_cumu[cluster_no - 1] *
		(long double)(mt_rand()+1.) / (mt_rand.max()+1.);
	for (cIndex = 0; clu_receptor_m_cumu[cIndex] < r3; cIndex++);

	// methylation event in cluster cIndex
	// active or inactive receptor? -> sample
	r4 = (clu_active_receptors[cIndex][level]+clu_inactive_receptors[cIndex][level]) *
		(long double)(mt_rand()+1.) / (mt_rand.max()+1.);
	if(r4<clu_active_receptors[cIndex][level]){ // methylated receptor is active
		clu_active_receptors[cIndex][level]--;
		clu_active_receptors[cIndex][level+1]++;
		glob_active_receptors[level]--;
		glob_active_receptors[level+1]++;}
	else{ // methylated receptor is inactive
		clu_inactive_receptors[cIndex][level]--;
		clu_inactive_receptors[cIndex][level+1]++;}


}
void SampleDemethylation(int level){
	// demethylation process, only active receptors can be demethylated
	// which cluster
	// calculate cumulative receptor distribution over clusters
	clu_receptor_m_cumu[0] = clu_active_receptors[0][level];
	for(int cc=1; cc<cluster_no; cc++){
		clu_receptor_m_cumu[cc] = clu_active_receptors[cc][level] +
			clu_receptor_m_cumu[cc-1];
	}

	r3 = clu_receptor_m_cumu[cluster_no - 1] *
		(long double)(mt_rand()+1.) / (mt_rand.max()+1.);
	for (cIndex = 0; clu_receptor_m_cumu[cIndex] < r3; cIndex++);

	// methylation event in cluster cIndex
	// active or inactive receptor? only active can be demethylated -> no sample
	// what if active level 1 receptor is demethylated?? cannot have active receptors in level 0
	clu_active_receptors[cIndex][level]--;

	//clu_inactive_receptors[cIndex][level - 1]++;

	glob_active_receptors[level]--;
    //if(!(level==1)){
	clu_active_receptors[cIndex][level - 1]++;
	glob_active_receptors[level-1]++;
	//}


}
void UpdateAmu(int recalc_index, double* amu, unsigned long long int* x, bool start){
	double new_amu;
	if (start){
		rIndex = recalc_index;
	}

	switch (recalc_index){
		case 0:
			new_amu= tau_factor*x[0] * amu_const2;
			break;
		case 1:
			new_amu= tau_factor*x[1] * amu_const2;
			break;
		case 2:
			new_amu= tau_factor*x[2] * amu_const2;
			break;
		case 3:
			new_amu= tau_factor*x[3] * amu_const2;
			break;
		case 4:
			new_amu= tau_factor*T_act_list[1] * amu_const3;
			break;
		case 5:
			new_amu= tau_factor*T_act_list[2] * amu_const3;
			break;
		case 6:
			new_amu= tau_factor*T_act_list[3] * amu_const3;
			break;
		case 7:
			new_amu= tau_factor*T_act_list[4] * amu_const3;
			break;
		case 8:
			new_amu= (kA * T_act * (CheAtot * f - x[5]));
			break;
		case 9:
			new_amu= (kB_prime * (x[5] / f) * (CheBtot * f - x[6]));
			break;
		case 10:
			new_amu = (gamB * x[6]);
			break;
		case 11:
			new_amu = (kY * (x[5]/f) * (CheYtot * f - x[7]));
			break;
		case 12:
			new_amu = ((kZ * CheZ+gamY) * x[7]) ;
			break;
		case 13:
			new_amu = (x[8] / t0) * exp(-20 + (40 * (x[7] / f) / ((x[7] / f) + 3.06))) ;
			break;
		case 14:
			new_amu = ((motors - x[8]) / t0) * exp(20 - (40 * (x[7] / f) / ((x[7] / f) + 3.06)));
			break;
		case 15:
			new_amu = clu_switch_active_prop_msum_cumu[cluster_no - 1] ;
			break;
		case 16:
			new_amu = clu_switch_inactive_prop_msum_cumu[cluster_no - 1] ;
			break;
	}

	//update of Tau_recalc_index
	if (recalc_index == rIndex){
		r1 = (long double)(mt_rand()+1.)/(mt_rand.max()+1.);

		double new_tau = currentTime - (log(r1) / new_amu);
		tree_node_vec[tree_pointer_vec[recalc_index]].tau = new_tau;
	}
	else{
		tree_node_vec[tree_pointer_vec[recalc_index]].tau = (amu[recalc_index]/new_amu)*
			(tree_node_vec[tree_pointer_vec[recalc_index]].tau - currentTime) +
			currentTime;
		if (amu[recalc_index] == 0 && new_amu != 0) { // weird case of amu=0 -> tau=inf, no rescaling possible
			// draw new random number
			r1 = (long double)(mt_rand() + 1.) / (mt_rand.max() + 1.);
			tree_node_vec[tree_pointer_vec[recalc_index]].tau = currentTime + (log(1/r1) / new_amu);

		}
		if (new_amu == 0) {
			tree_node_vec[tree_pointer_vec[recalc_index]].tau = r1 / new_amu; // create inf
		}

	}

	amu[recalc_index] = new_amu;
}
double genNormalDist(double mu, double sig)
{

    long double v1 = (long double)(mt_rand()+1.) / (mt_rand.max()+1.);
    long double v2 = (long double)(mt_rand()+1.) / (mt_rand.max()+1.);
    double u1 = cos(2 * 3.141 * v2) * sqrt(-2. * log(v1));
    double var = u1 * (sig) + (mu);
    return(var);
}

void GeneratePutativeTimes(double* amu, double* amu_cumu, unsigned long long int* x)
{
	for(int tt=0; tt<n_reactions; tt++){
		r1 = (long double)(mt_rand()+1.)/(mt_rand.max()+1.);
		putative_tau_list[tt] = -log(r1)/amu[tt];
		tree_node_vec[tree_pointer_vec[tt]].tau = putative_tau_list[tt];
		tree_node_vec[tree_pointer_vec[tt]].reaction = tt;
	}
	return;
}
