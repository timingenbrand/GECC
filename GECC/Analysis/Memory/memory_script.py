### Memory Analysis SNM
import numpy as np
import matplotlib.pyplot as plt
import scipy.special as spec
import sys

input = float(sys.argv[1])

n_bact = 100
time_org = 500
lam = 0.005
v = 1.4
tau_fac = 1
rec_fac = input


rec_fac = input

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
# Kraskov Estimator, first algorithm

def MI_first(k,t_id):
    x_list = np.zeros(n_bact)
    y_list = np.zeros((n_bact,5))
    z_list = np.zeros((n_bact,6))

    for i in range(n_bact):
        #x_list[i] = data_list[i][t_id,1]  # L, concentration
        x_list[i] = 1000*data_list[i][t_id,1]  # L, concentration
        y_list[i,:] = data_list[i][t_id,2:7] # T, methylation
        z_list[i,:] = data_list[i][t_id,1:7] # x and y combined
        z_list[i,0] *= 1000
    noise_list = np.random.normal(0, 1e-8, (n_bact, 6))
    z_list += noise_list
    x_list += noise_list[:,0]
    y_list += noise_list[:,1:6]


    d_mat = np.zeros((n_bact,n_bact)) # "distance" matrix
    dx_mat = np.zeros((n_bact,n_bact)) # "distance" matrix in x
    dy_mat = np.zeros((n_bact,n_bact)) # "distance" matrix in y
    for i in range(n_bact):
        for j in range(n_bact):
            dx_mat[i,j] = np.linalg.norm(x_list[i] - x_list[j])
            dy_mat[i,j] = np.linalg.norm(y_list[i,:] - y_list[j,:])
            d_mat[i,j] = np.maximum(dx_mat[i,j], dy_mat[i,j])

    # ranking all neighbors for every cell
    d_rank = np.zeros((n_bact,n_bact))
    #dx_rank = np.zeros((n_bact,n_bact))
    #dy_rank = np.zeros((n_bact,n_bact))
    for i in range(n_bact):
        distances = d_mat[i,:]
        d_rank[i,:] = np.argsort(distances)
        #xdistances = dx_mat[i,:]
        #dx_rank[i,:] = np.argsort(xdistances)
        #ydistances = dy_mat[i,:]
        #dy_rank[i,:] = np.argsort(ydistances)


    nx = np.zeros(n_bact)
    ny = np.zeros(n_bact)
    for i in range(n_bact):
        #kth_distance = d_mat[i, int(d_rank[i,k])] # epsilon (i) /2
        # check if dx or dy is larger for k-th neighbor
        epsilon = d_mat[i,int(d_rank[i,k])]
        #print(dx)
        #print(dy)

        #ny
        for j in range(n_bact): #brute force variante, kein sortieren
            ydist = dy_mat[i,j]
            if ydist < epsilon:		
                ny[i] += 1

        ny[i] -= 1 # delete count of self
        #nx
        for j in range(n_bact): #brute force variante, kein sortieren
            xdist = dx_mat[i,j]
            if xdist < epsilon:
                nx[i] += 1

        nx[i] -= 1 # delete count of self
    digam_x = spec.digamma(nx+1)
    digam_y = spec.digamma(ny+1)
    #print(nx)
    #print(ny)
    #print(spec.digamma(k))
    #print(spec.digamma(n_bact))
    MI_val = (spec.digamma(k) - np.mean(digam_x + digam_y) + spec.digamma(n_bact)) / np.log(2)
    return MI_val


k = 3
start = 1000
stop = 4000
step = 10
tau = np.arange(start,stop,step)
length = len(tau)
y1 = np.zeros(length)
for i in range(length):
    y1[i] = MI_first(k, tau[i])
    #y2[i] = MI_second(k,tau[i])

plt.plot(tau/10-100, y1, label="Kraskov-1")
plt.xlabel("$\\tau [s]$")
plt.ylabel("$ I~( L_{step}, T_{\\tau} )$ [bits] ")
plt.title("Kraskov-1, k = {}, $L_+$ = (0.1-0.3)mM, L in $\mu$M".format(k))
plt.tight_layout()
plt.savefig("../results/mi_kraskov_k{}_{:.5g}.png".format(k,input))

data = np.zeros((2,length))
data[0,:] = tau/10
data[1,:] = y1
outF = open("../results/mi_kraskov_k{}_{:.5g}.csv".format(k,input),"w")
outF.write("t [s]; MI [bits]\n")
for i in range(length):
	outF.write(str(data[0,i]))
	outF.write(";")
	outF.write(str(data[1,i]))
	outF.write(";\n")

outF.close()
print("Memory Calc done! Input: {}".format(input))