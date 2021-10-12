//#pragma once
#include <string>
#include <random>
int Simulation(std::string filename = "");

double genNormalDist(double mu, double sig);
void Movement(double time);
void SetUp(unsigned long long int* x);
void Reactions(int reaction_index, unsigned long long int* x);
void UpdateAmu(int recalc_index, double* amu, unsigned long long int* x, bool start);
void CalcActivationProp(unsigned long long int* x, double* amu);

void Output(double* nextStoptime, unsigned long long int* x, std::string filename);
void ParamOutput(std::string filename);

void SampleMethylation(int level);
void SampleDemethylation(int level);

void CreateClusters(unsigned long long int* x);
void DistributeReceptors(int index, unsigned long long int* x, std::vector<int>& clustersizes);

void GeneratePutativeTimes(double* amu, double* amu_cumu, unsigned long long int* x);
void CreateTreeStructure();
void SortTree();
void CalculateAmu(double* amu, double* amu_cumu, unsigned long long int* x, bool start);
