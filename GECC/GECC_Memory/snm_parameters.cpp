#include <iostream>
#include <fstream>
#include <string>
#include "snm_functions.h"
#include "snm_variables.h"
#include <math.h>
using namespace std;

void Output(double* nextStoptime, unsigned long long int* x, string filename)
{
    ofstream file;
    if (noutput == 0) {
        file.open(filename, fstream::trunc);
        file << "t [s]; L [uM]; T0 [uM]; T1 [uM]; T2 [uM]; T3 [uM]; T4 [uM]; CheAp [uM]; CheBp [uM]; CheYp [uM]; CCW_motors; T_act [uM]; Posx [um]; Posy [um]; Angle [rad]\n";
        noutput = 1;
    }
    else {
        file.open(filename, fstream::app);
    }
    file << *nextStoptime << ";" << lig_conc << ";" << x[0]/f << ";";
    file << x[1] / f << ";" << x[2] / f << ";" << x[3] / f << ";";
    file << x[4] / f << ";" << x[5] / f << ";" << x[6] / f << ";" << x[7] / f << ";" << x[8];
    file << ";" << T_act << ";" << posx << ";" << posy << ";" << angle  << endl;
    file.close();
    return;
}

void ParamOutput(string p_filename)
{
    ofstream p_file;
    p_file.open(p_filename, fstream::trunc);

    p_file << "Runtime " << endTime << " s" << endl;
    p_file << "dt " << dt << " s" << endl;
    p_file << "Seed " << seed << endl;
    p_file << "Box_x " << box_x << " um" << endl;
    p_file << "Box_y " << box_y << " um" << endl;
    p_file << "Motors " << motors << endl;
	p_file << "MemorySpeedFactor " << tau_factor << endl;
    p_file << "Gradient_lambda " << lambda << " 1/um" << endl;
    p_file << "Motor_SwitchConst " << t0 << " s"<< endl;
    p_file << "Rot_Diffusion " << Dr <<  " rad/s" << endl;
    p_file << "Cell_Velocity " << v0 << " um/s" << endl;
    p_file << "Volume " << vol*1e15 << "fL" << endl;

    p_file.close();
    return;

}

void WriteSeeds(string s_filename, int count)
{
	ofstream s_file;
	s_file.open(s_filename, fstream::app);
	s_file << count << "; " << seed << endl;
	s_file.close();
	return;
}
