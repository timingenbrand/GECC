import numpy as np
import matplotlib.pyplot as plt
import pathlib as ptlib
import glob
import re
import os
import sys

log_bool = int(sys.argv[1])
lam = float(sys.argv[2])
motors = 3
if log_bool:
    os.chdir("../data/.log_lam{}".format(lam))
else:
    os.chdir("../data/.lam{}".format(lam))
folder_names = np.array(glob.glob("n*"))

n = len(folder_names)
inputs = np.zeros(len(folder_names))
parameter_names = ["n", "t", "lam", "v", "tau", "mov"]
changing_par = 4
second = 5
n_bact = 250
n_par = len(parameter_names)



def analysis(cell):
    total_time = data_list[cell][-1,0]
    total_steps = len(data_list[cell][:,0])
    current_state = True # 1 = run, 0 = tumble


    run_lengths = []
    run_breaks = [] # increasing lig = 1, decreasing lig = 0
    tumble_lengths = []
    switch_count = 0
    time_count = 0
    curr_runlength = 0
    curr_tumblelength = 0
    wrong_run_lengths = []

    currently_wrong = False
    current_wrong_run = 0
    min_c = 0.01
    max_c = 1000
    for t in range(total_steps):

        time_count += 0.1

        if current_state:
            if data_list[cell][t,1] > data_list[cell][t-1,1]:
                currently_wrong = False
                current_wrong_run = 0
            else:
                currently_wrong = True
                current_wrong_run += 0.1
            curr_runlength += 0.1
            if data_list[cell][t, 10] < motors:
                current_state = False
                switch_count += 1
                run_lengths.append(curr_runlength)
                if currently_wrong:
                    wrong_run_lengths.append(current_wrong_run)
                    current_wrong_run = 0

                curr_runlength = 0
                if data_list[cell][t,1] > data_list[cell][t-1,1]:
                    run_breaks.append(True)
                else:
                    run_breaks.append(False)
        else:
            curr_tumblelength += 0.1
            if data_list[cell][t, 10] > (motors-1):
                current_state = True
                switch_count += 1
                tumble_lengths.append(curr_tumblelength)
                curr_tumblelength = 0


    return [run_lengths, run_breaks, tumble_lengths, wrong_run_lengths]





for ff in range(n):
    parameters = np.array(re.findall(r"[-+]?\d*\.\d+|\d+", folder_names[ff]),dtype="float")

    count = 0
    os.chdir(folder_names[ff])
    file_names = np.array(glob.glob("bact*"))
    os.chdir("..")
    #print(file_names)
    data_list = []
    for i in range(len(file_names)):
        try:
            #print("./"+folder_names[ff]+"/"+file_names[i])
            data = np.genfromtxt("./"+folder_names[ff]+"/"+file_names[i], skip_header = 1, delimiter = ";")
            #print(i, data.shape)
            if data[-1,0] > parameters[1]-1:
                data_list.append(data)
                count += 1
        except:
            #print("{} failed".format(i))
            pass

    if (n_bact>len(data)):
        print("Parameter {} contained {} instead of {} cells!".format(parameters[changing_par],
                                                                  len(data), n_bact))
    n_bact = len(data_list)

    print("Data loaded... {} cells".format(n_bact))


    run_length = []
    run_break = []
    tumble_length = []
    wrong_run_length = []

    #data = [ [], [], [], [] ]
    for i in range(n_bact):
        data = analysis(i)
        run_length.extend(data[0])
        run_break.extend(data[1])
        tumble_length.extend(data[2])
        wrong_run_length.extend(data[3])
        #print("Cell {} done!".format(i))

        #print("Averaging now...")
    avg_run = np.average(run_length)
    std_run = np.std(run_length)
    avg_break = np.average(run_break)
    std_break = np.std(run_break)
    avg_tumble = np.average(tumble_length)
    std_tumble = np.std(tumble_length)
    avg_wrong = np.average(wrong_run_length)
    std_wrong = np.std(wrong_run_length)


    #np.savetxt(data, "switching.csv", header="Switchrate [1/s], Avg_Run [s], Std_Run [s], Good_Run_Breaks [%], Avg_Tumble [s], Std_Tumble [s], Avg_Wrongrun [s], Std_Wrongrun [s]")

    if (not log_bool):
        filename = "runlen_{:.5g}_lin.CSV".format(lam)
    else:
        filename ="runlen_{:.5g}_log.CSV".format(lam)
    header = True
    if ptlib.Path("../../results/"+filename).is_file():
        header = False

    outF = open("../../results/"+filename, "a")
    if header:
        outF.write("Tau; Mov; Switchrate [1/s]; Avg_Run [s]; Std_Run [s]; Good_Run_Breaks [%]; Std_Good_Run_Breaks[%]; Avg_Tumble [s]; Std_Tumble [s]; Avg_Wrongrun [s]; Std_Wrongrun [s]\n")
    outF.write("{}; {}; {}; {}; {}; {}; {}; {}; {}; {}; {}\n".format(parameters[changing_par], parameters[second], avg_run, std_run,
        avg_break, std_break, avg_tumble, std_tumble, avg_wrong, std_wrong))
    outF.close()
    print("Parameter set {} done!".format(ff))
