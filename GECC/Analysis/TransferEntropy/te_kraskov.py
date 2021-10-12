import numpy as np
from jpype import *
import scipy.stats as sp
import pathlib as ptlib
import sys
import time

Time0 = time.time()
# need ligand and methylation data in double[][] format
# ligand = [[0], [1], [2], ...]
# methyl = [[0, 0, 0, 0, 0,], [1, 1, 1, 1, 1], ...]

# transfer entropy parameters

dt = 0.1 # interval between history_samples
start_TE = 50 # in seconds
 # in seconds
ind_target = [2, 3, 4, 5, 6]
ind_source = [1]

# load data
input1 = float(sys.argv[1])
input2 = float(sys.argv[2])
dt = input2

history_samples = int(440 / dt)
n_bact = 150
time_org = 500
lam = 0.005
v = 1.4
tau = 1
rec = input1

folder = "../data/n{}_t{}_lam{:.5g}_v{:.5g}_tau{:.5g}_rec{:.5g}/".format(n_bact, time_org, lam, v, tau, rec)
#folder="../../testdata/"
n_bact = 1500
data_list = []
print("Loading data from ... ")
print(folder)

count = 0
for i in range(n_bact):
    file = "bact{}.csv".format(i)
    #print(folder+file)
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
print("Loading data done! Start TE Analysis...")
###


end_TE = start_TE + history_samples*dt # in seconds
start_TE *= 10 # to convert seconds to bin-number, still integer?
end_TE *= 10
dt_bins = dt/0.1
TE_list = np.zeros(n_bact)

len_ind_source = len(ind_source)
len_ind_target = len(ind_target)

# start jvm
jarLocation = "infodynamics-dist-1.5/infodynamics.jar"
startJVM(getDefaultJVMPath(), "-Djava.class.path=" + jarLocation)

teCalcClass = JPackage("infodynamics.measures.continuous.kraskov").TransferEntropyCalculatorMultiVariateKraskov
teCalc = teCalcClass()
teCalc.initialise(1, 5)


for cell in range(n_bact):
	# prepare ligand and methylation data
	source = []
	target = []
	teCalc.startAddObservations()
	
	for timestep in range(history_samples):
		source_temp = []
		for ss in range(len_ind_source):
			try:          
				#print(counto)
				source_temp.append(float(   
			    	data_list[cell][int(np.floor(start_TE+dt_bins*timestep)-1), ind_source[ss]]))
			except:
				continue
				#print("Corresponding timebin: {}".format(np.floor(start_TE+dt_bins*timestep)-1))
				#print("Len of source timeseries: {}".format(len(data_list[cell][:,ind_source[ss]])))

		target_temp = []
		for ss in range(len_ind_target):
			try:
				target_temp.append(float(
                		data_list[cell][int(np.floor(start_TE+dt_bins*timestep)-1), ind_target[ss]]))
			except:
				continue
				#print("Corresponding timebin: {}".format(np.floor(start_TE+dt_bins*timestep)-1))
				#print("Len of target timeseries: {}".format(len(data_list[cell][:,ind_target[ss]])))
		#print(type(target_temp))
		#print(type(target_temp[0]))
		if (len(source_temp) > 0 and len(target_temp) > 0): 
			source.append(source_temp)
			target.append(target_temp)
	#teCalc.addObservations(source, target)

	try:
		#print(source)
		#teCalc.addObservations(source, target)
		#print(len(source), len(source[0]), len(target), len(target[0]) )
        
		teCalc.addObservations(source, target, 0, len(source))
	except: 
		#print(source)
		print("Cell could not be added to Observations. Cell: {}; Len(source): {}, Len(target): {}".format(cell, len(source), len(target)))
		#continue


teCalc.finaliseAddObservations()
print(teCalc.getNumObservations())
print(teCalc.getAddedMoreThanOneObservationSet())
TE_final = teCalc.computeAverageLocalOfObservations()
print(TE_final)


print("Starting Entropy Rate Analysis!")

eCalcClass = JPackage("infodynamics.measures.continuous.kernel").EntropyCalculatorKernel
eCalc = eCalcClass()

entropy_rates = []
eCalc.initialise()

for cell in range(n_bact):
	#ligand = data_list[cell][int(np.floor(start_TE+dt_bins*timestep)-1), 1]
	ligand = []
	#ligand = data_list[cell][start_TE*10:history_samples+start_TE*10, 1]
	ligand = data_list[cell][:,1]
	#print(data_list[cell][0,1])
	#print(ligand)
	eCalc.setObservations(ligand)
	obs_num = eCalc.getNumObservations()
	entropy = eCalc.computeAverageLocalOfObservations()
	entropy_rates.append(entropy / obs_num)

er_avg = np.average(entropy_rates)
er_std = np.std(entropy_rates)



Time1 = time.time()
Time_diff = (Time1-Time0)/60.

print("Entropy Analysis done! It took {} minutes. Printing results into file...".format(Time_diff))


header = True
folder_clean = "n{}_t{}_lam{:.5g}_v{:.5g}_tau{:.5g}_rec{:.5g}/".format(n_bact, time_org, lam, v, tau, rec)

#filename = "../results/"+folder_clean+"TE_dt{}.CSV".format(dt)
filename = "TE_dt{}.CSV".format(dt)
if ptlib.Path(filename).is_file():
	header = False

outF = open(filename, "a")
if header:
	outF.write("rec; TE [bit]; ER [bit/step]; ER_std [bit/step] n_bact; lambda[1/um]; v[fL]; tau; rec; startTE; history_samples; dt [s]; calctime [min]\n")
outF.write(str(rec))
outF.write(";")
outF.write(str(TE_final*(1/np.log(2))))
outF.write(";")
outF.write(str(er_avg*(1/np.log(2))))
outF.write(";")
outF.write(str(er_std*(1/np.log(2))))
outF.write(";")
outF.write(str(n_bact))
outF.write(";")
outF.write(str(lam))
outF.write(";")
outF.write(str(v))
outF.write(";")
outF.write(str(tau))
outF.write(";")
outF.write(str(rec))
outF.write(";")
outF.write(str(start_TE/10))
outF.write(";")
outF.write(str(history_samples))
outF.write(";")
outF.write(str(dt))
outF.write(";")
outF.write(str(Time_diff))
outF.write("\n")

outF.close()

print("Printing done!")
