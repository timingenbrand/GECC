import numpy as np
import sys
import pathlib as ptlib
# need ligand and methylation data in double[][] format
# ligand = [[0], [1], [2], ...]
# methyl = [[0, 0, 0, 0, 0,], [1, 1, 1, 1, 1], ...]

# load data
input1 = float(sys.argv[1])
#input2 = float(sys.argv[2])


n_bact = 200
time_org = 500
lam = input1
v = 1.4
tau = 1
rec = 1
folder = "../data/n{}_t{}_lam{:.5g}_v{:.5g}_tau{:.5g}_mov{:.5g}/".format(n_bact, time_org, lam, v, tau, rec)
n_bact = 1000

data_list = []
print("Loading data from ... ")
print(folder)

count = 0
for i in range(n_bact):
    file = "bact{}.csv".format(i)
    try:
        data = np.genfromtxt(folder+file, skip_header = 1, delimiter = ";")

        count += 1
        #print(i, data.shape)
        data_list.append(data)
    except:
        #print("{} failed".format(i))
        pass
n_bact = count
print(count)
print("Loading data done!")


start_x = 2500
start_y = 10000
checktime = 499 # seconds
checkbin = int(checktime*10)
list_enddist2 = []
list_enddistx2 = []
list_enddisty2 = []
for i in range(n_bact):
    try:
        dx = abs(data_list[i][checkbin,12] - start_x)
        dy = abs(data_list[i][checkbin,13] - start_y)

        list_enddist2.append((dx)**2 + (dy)**2)
        list_enddistx2.append((dx)**2)
        list_enddisty2.append((dy)**2)
    except:
        print("Cell {} was not simulated for {} seconds!".format(i, checktime))


diffusion = np.average(list_enddist2) / (2*checktime)
std_err_diffusion = np.std(list_enddist2) / (2*checktime*np.sqrt(len(list_enddist2)))
diffusion_x = np.average(list_enddistx2) / (2*checktime)
diffusion_y = np.average(list_enddisty2) / (2*checktime)

filename = "../results/diffusion.CSV"
if ptlib.Path(filename).is_file():
	header = False

outF = open(filename, "a")
if header:
	outF.write("input; diff_coeff [um^2/s]; diff_coeff_x [um^2/s]; diff_coeff_y [um^2/s]\n")



### Runmode % analysis
mot = 3
offset = 500 # in bins
run_perc_list = []
for i in range(n_bact):
    timesteps = len(data_list[i][:,0]) - offset
    tum_count = 0
    for tt in range(timesteps):
        if (data_list[i][tt+offset,10] < (mot-0.5)):
            tum_count += 1
    run_perc_list.append(1-(tum_count/timesteps))

        
run_perc = np.average(run_perc_list)
std_err_run_perc = np.std(run_perc_list) / (np.sqrt(len(run_perc_list)))




# write diff_coeff to shared file

outF.write(str(input1))
outF.write(";")
outF.write(str(diffusion))
outF.write(";")
outF.write(str(diffusion_x))
outF.write(";")
outF.write(str(diffusion_y))
outF.write(";")
outF.write(str(run_perc))
outF.write(";")
outF.write(str(std_err_diffusion))
outF.write(";")
outF.write(str(std_err_run_perc))
outF.write("\n")
outF.close()
