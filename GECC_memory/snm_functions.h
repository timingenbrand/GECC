//#pragma once
#include <string>
#include <random>
int Simulation(std::string filename = "");

double genNormalDist(double mu, double sig);
void Movement(double time);
void SetUp(unsigned long long int* x);
void Reactions(int reaction_index, unsigned long long int* x);
void CalculateAmu(double* amu, unsigned long long int* x);
void Output(double* nextStoptime, unsigned long long int* x, std::string filename);
void ParamOutput(std::string filename);
void WriteSeeds(std::string s_filename, int count);
