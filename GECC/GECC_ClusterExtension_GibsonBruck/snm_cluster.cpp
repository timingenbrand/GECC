#include <iostream>
#include <math.h>
#include "snm_functions.h"
#include "snm_variables.h"
#include <random>
using namespace std;
void CreateClusters(unsigned long long int* x){
	double prelim_receptors = CheAtot * f;
	cluster_no = (int)((prelim_receptors / cluster_size)+0.5); // rounding
	cluster_size = (int)((prelim_receptors / cluster_no)+0.5); //rounding
	n_recep = cluster_no*cluster_size;
	//cout <<endl << "Lost/added receptors: " << n_recep-prelim_receptors << endl;
	
    x[0] = abs((int)(n_recep - (x[1] + x[2] + x[3] + x[4])));

	vector<int> dummy(5, 0);
	vector<double> dummy_double(5, 0.);
	// inner vectors are 5 elements long due to 5 meth. level
	recalc_list = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
								12, 13, 14, 15, 16 };
	clu_active_receptors.resize(0, dummy);
	clu_inactive_receptors.resize(0, dummy);
	clu_switch_active_prop.resize(0, dummy_double);
	clu_switch_inactive_prop.resize(0, dummy_double);
	clu_switch_active_prop_msum.resize(0, 0.);
	clu_switch_inactive_prop_msum.resize(0, 0.);
	clu_switch_active_prop_msum_cumu.resize(0, 0.);
	clu_switch_inactive_prop_msum_cumu.resize(0, 0.);
	clu_receptor_m_cumu.resize(0, 0.);
	glob_active_receptors.resize(0, 0); // 5 methylation levels
	clu_active_percent.resize(0, 0.);


	clu_active_receptors.resize(cluster_no, dummy);
	clu_inactive_receptors.resize(cluster_no, dummy);
	clu_switch_active_prop.resize(cluster_no, dummy_double);
	clu_switch_inactive_prop.resize(cluster_no, dummy_double);
	clu_switch_active_prop_msum.resize(cluster_no, 0.);
	clu_switch_inactive_prop_msum.resize(cluster_no, 0.);
	clu_switch_active_prop_msum_cumu.resize(cluster_no, 0.);
	clu_switch_inactive_prop_msum_cumu.resize(cluster_no, 0.);
	clu_receptor_m_cumu.resize(cluster_no, 0.);

	glob_active_receptors.resize(5, 0); // 5 methylation levels
	clu_active_percent.resize(cluster_no, 0.);
	vector<int> clustersizes(cluster_no, 0);
	DistributeReceptors(0, x, clustersizes);
	DistributeReceptors(1, x, clustersizes);
	DistributeReceptors(2, x, clustersizes);
	DistributeReceptors(3, x, clustersizes);
	DistributeReceptors(4, x, clustersizes);

	for (int cc=0; cc<cluster_no; cc++){
		for (int mm=0; mm<5; mm++){
			clu_active_percent[cc] += clu_active_receptors[cc][mm];
		}
		clu_active_percent[cc] /= cluster_size;
	}
	T_act = 0.;
	for (int mm = 0; mm<5; mm++){
		T_act_list[mm] = glob_active_receptors[mm] / f;
		T_act += T_act_list[mm];
	}

}


void DistributeReceptors(int index, unsigned long long int* x, vector<int>& clustersizes){

	double var1;
	int var2;
	bool active = false;
	for (int cc=0; cc<x[index];cc++){
		if (index != 0){ // receptors of methylation level 0 cannot be active
			var1 = (double)(mt_rand()+1.)/(mt_rand.max()+1.);
			active = false;
			if (var1<0.2){

					active = true;
			}
		}
		var2 =(int)cluster_no*(mt_rand()+1.)/(mt_rand.max()+1.);
		int ref = var2;
		while ((clustersizes[ref]) >= cluster_size){
			ref++;
			if (ref>=cluster_no){
				ref = 0;
			}
		}
		(clustersizes[ref])++;
		if (active){
			clu_active_receptors[ref][index]++;
			glob_active_receptors[index]++;
		}
		else{
			clu_inactive_receptors[ref][index]++;
		}
	}
	return;
}
