### FULL DRIFT SPEED ANALYSIS
import numpy as np
import matplotlib.pyplot as plt
import sys
import os
import scipy.stats as sta
# LOADING DATA
input = float(sys.argv[1])
print(input)
# change input variable for anlysis
n_bact = 150
time_org = 500
lam = input
v = 1.4
tau_factor = 1
rec = input

save_folder = "../results/n{}_t{}_lam{}_v{:.5g}_tau{}_rec{:.5g}/".format(n_bact, time_org, lam, v, tau_factor,rec)

try:
    os.mkdir(save_folder)
except:
    print("folder already existed")
folder = "../data/n{}_t{}_lam{}_v{:.5g}_tau{}_rec{:.5g}/".format(n_bact, time_org, lam, v, tau_factor,rec)

print(folder)
print(save_folder)
n_bact = 1500
data_list = []

count = 0
for i in range(n_bact):
    file = "bact{}.csv".format(i)
    print(folder+file)
    try:
        data = np.genfromtxt(folder+file, skip_header = 1, delimiter = ";")
        count += 1
        #print(i, data.shape)
        if data[-1,0] > time_org-1:
            data_list.append(data)
    except:
        #print("{} failed".format(i))
        pass
n_bact = len(data_list)

print("Data loaded... {} cells".format(n_bact))



### DRIFT SPEED

cell_velx_list = []
cell_velx_var_list = []
cell_velx_count_list = []
cell_endpos_list = []
for cc in range(n_bact):
    velx_list = []
    for tt in range(len(data_list[cc][:,0])-1):
        # go from timestep tt to timestep tt+1 and look at posx difference
        concentration = data_list[cc][tt,1]
        if ((concentration>0.01) and (concentration<1000)):
            covered_distance = data_list[cc][tt,12] - data_list[cc][tt+1,12]
            time_passed = data_list[cc][tt,0] - data_list[cc][tt+1,0] # should be constant =0.1
            velx_list.append(covered_distance/time_passed)

    if (len(velx_list)>1000):
        cell_velx_list.append(np.mean(velx_list))
        cell_velx_var_list.append(np.var(velx_list))
        cell_velx_count_list.append(len(velx_list))
        cell_endpos_list.append(data_list[cc][-1,12])

n_data = len(cell_velx_list)
vd = np.average(cell_velx_list, weights=cell_velx_count_list)
var_vd = np.sum(cell_velx_count_list*((cell_velx_list-vd)**2))/np.sum(np.array(cell_velx_count_list)-1)
std_vd = np.sqrt(var_vd)
std_avgvd = std_vd / np.sqrt(n_data)
avg_endpos = np.average(cell_endpos_list)
var_endpos = np.var(cell_endpos_list)
std_endpos = np.sqrt(var_endpos)
std_avgendpos = std_endpos / np.sqrt(n_data)
# write drift velocity to shared file
outF = open("../results/vd_results_recscan_lam{}.CSV".format(lam), "a")
#outF.write("# v={}, c={}\n".format(v,clu))
outF.write("#input; vd; std(vd); std(avg_vd); avg_endpos; std(endpos); std(avg_endpos)\n")
outF.write(str(input))
outF.write(";")
outF.write(str(vd))
outF.write(";")
outF.write(str(std_vd))
outF.write(";")
outF.write(str(std_avgvd))
outF.write(";")

outF.write(str(avg_endpos))
outF.write(";")
outF.write(str(std_endpos))
outF.write(";")
outF.write(str(std_avgendpos))
outF.write(";")

outF.write("\n")
outF.close()

plt.hist(cell_velx_list, bins=96,color="black", range=(-12,+12),
      weights=np.ones(len(cell_velx_list))/len(cell_velx_list))
plt.ylabel("Normed Cell Distribution")
plt.xlabel("Drift Speed [$\mu$m/s]")
plt.savefig(save_folder+"vd_dist.pdf")
plt.close()
