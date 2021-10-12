
# Initializing all constant parameters for E. coli simulation

parameters = read.table("Parameters.csv", header=TRUE,sep=";")


n_bact = parameters[1,3]
steps = parameters[2,3]
#box_dim = c(parameters[3,3],parameters[4,3])

#t0 = parameters[5,3]
dt = parameters[3,3]

total_runtime = dt*steps
save_intervall = parameters[4,3]
n_saves = steps/save_intervall
Atot = parameters[5,3]
Ytot = parameters[6,3]
Btot = parameters[7,3]
Rtot = parameters[8,3]
Ztot = parameters[9,3]
Ttot = Atot
kA = parameters[10,3]
kY = parameters[11,3]
kZ = parameters[12,3]

gamY = parameters[13,3]
kB_prime = parameters[14,3]
gamB = parameters[15,3]
kR = parameters[16,3]
KR = parameters[17,3]
kB = parameters[18,3]
KB = parameters[19,3]


Ytot_org = Ytot
Atot_org = Atot
Rtot_org = Rtot
Btot_org = Btot
Ztot_org = Ztot
rm(parameters)
