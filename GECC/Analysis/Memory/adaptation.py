### Memory Analysis SNM
import numpy as np
import matplotlib.pyplot as plt
import scipy.special as spec
import sys

n_bact = 100
time_org = 500
lam = 0.005
v = 1.4
tau_fac = 1
rec_fac = 1


folder = "../data/n{}_t{}_lam{:.5g}_v{:.5g}_tau{:.5g}_rec{:.5g}/".format(n_bact,time_org, lam, v, tau_fac, rec_fac)
print("Folder: ")
print(folder)
save_folder = "../results/n{}_t{}_lam{:.5g}_v{:.5g}_tau{:.5g}_rec{:.5g}/".format(n_bact,time_org, lam, v, tau_fac, rec_fac)
n_bact = 1000
data_list = []

for i in range(n_bact):
    file = "bact{}.csv".format(i+0)
    try:
        data = np.genfromtxt(folder+file, skip_header = 1, delimiter = ";")
        if (data[-1,0] > 400):
            data_list.append(data)
    except:
        continue

n_bact = len(data_list)
time = data[:,0]

cheyp = 0
cheap = 0
chebp = 0

cheyp_list = []
cheap_list = []
chebp_list = []

for tt in range(len(data[:,0])):
    cheyp = 0
    cheap = 0
    chebp = 0
    for cc in range(n_bact):
        cheyp += data_list[cc][tt,9]
        chebp += data_list[cc][tt,8]
        cheap += data_list[cc][tt,7]
    cheyp_list.append(cheyp/n_bact)
    chebp_list.append(chebp/n_bact)
    cheap_list.append(cheap/n_bact)




data_out = np.zeros((n_bact*10,4))
data_out[:,0] = time
data_out[:,1] = np.array(cheap_list)
data_out[:,2] = np.array(chebp_list)
data_out[:,3] = np.array(cheyp_list)

np.savetxt("adaptation.csv", data_out, delimiter=";", header="Time [s]; Ap [uM]; Bp [uM]; Yp [uM]")


    
        