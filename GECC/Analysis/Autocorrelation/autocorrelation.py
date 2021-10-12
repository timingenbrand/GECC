import numpy as np
import matplotlib.pyplot as plt

dt = 0.1
max_time = 500

n_bact = 150
time_org = max_time
lam = 0.005

tau = 1
rec = 1
v = 1.4

folder= "../data/n{}_t{}_lam{:.5g}_v{:.5g}_tau{:.5g}_rec{:.5g}/".format(n_bact, time_org, lam, v, tau, rec)

n_bact = 1500
data_list = []
print(folder)

count = 0
for i in range(n_bact):
    file = "bact{}.csv".format(i)
    try:
        data = np.genfromtxt(folder+file, skip_header = 1, delimiter = ";")
        count += 1
        print(i, data.shape)
        time = data[:,0]
        data_list.append(data)
    except:
        print("{} failed".format(i))
        pass
n_bact = count
print(count)



def autocorr(t1, t2):
    x1_list = np.zeros(n_bact)
    x2_list = np.zeros(n_bact)
    for i in range(n_bact):
        x1_list[i] = data_list[i][int(np.round(t1*10,0)),14]
        x2_list[i] = data_list[i][int(np.round(t2*10,0)),14]
        
    mu1 = np.average(x1_list)
    mu2 = np.average(x2_list)
    sig1 = np.std(x1_list)
    sig2 = np.std(x2_list)
    cov = np.sum((x1_list-mu1)*(x2_list-mu2))
    cov /= n_bact
    autocorr = cov/(sig1*sig2)
    return autocorr


tau_list = np.arange(0,500,0.1)
autocorr_list = np.zeros(len(tau_list))
for j in range(len(tau_list)):
    autocorr_list[j] = autocorr(0, tau_list[j])
    
    

plt.plot(tau_list, autocorr_list)
plt.savefig("autocorr.png")
plt.close()

outF = open("../results/autocorrelation.csv","w")
outF.write("t [s]; autocorrelation\n")
for i in range(len(tau_list)):
    outF.write(str(tau_list[i]))
    outF.write(";")
    outF.write(str(autocorr_list[i]))
    outF.write(";\n")
outF.close()


