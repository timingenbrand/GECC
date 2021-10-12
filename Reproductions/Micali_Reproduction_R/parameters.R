
# Initializing all constant parameters for E. coli simulation

parameters = read.table("Parameters.CSV", header=TRUE,sep=";")


n_bact = parameters[1,3]
steps = parameters[2,3]
box_dim = c(parameters[3,3],parameters[4,3])

t0 = parameters[5,3]
dt = parameters[6,3]

total_runtime = dt*steps

grad_type = parameters[7,3]
grad_x0 = parameters[8,3]
grad_x1 = parameters[9,3]
grad_x2 = parameters[10,3]
grad_x3 = parameters[11,3]

v0 = parameters[12,3]
gam = parameters[13,3]
gam_R = parameters[14,3]
gam_B = parameters[15,3]

K_off_tsr = parameters[16,3]
K_on_tsr = parameters[17,3]
K_off_tar = parameters[18,3]
K_on_tar = parameters[19,3]
v_tsr = parameters[20,3]
v_tar = parameters[21,3]

kY = parameters[22,3]
kZ = parameters[23,3]
gam_Y = parameters[24,3]
Y_tot = parameters[25,3]
Z_tot = parameters[26,3]

save_intervall = parameters[27,3]
n_saves = steps / save_intervall

n_recep = parameters[28,3]
M = parameters[29,3]
tr = parameters[30,3]
Dr = parameters[31,3]
angle_sample = seq(0,pi, 0.001)
angle_dist = 0.5*(1+cos(angle_sample))*sin(angle_sample)
rm(parameters)
