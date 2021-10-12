
L = 0.1

Yp = 2.5
Bp = 0.072
Ap = 0.115

Tm = c(3.917,1.189,0.176,0.017,0.001)
T_act = c(0,0,0,0,0)


"
noise = get_factor(fold_expression)

Ytot_noise = noise
Atot_noise = noise
Rtot_noise = noise
Btot_noise = noise
Ztot_noise = noise
"
N_r = 0.9
alpha = 0.2
ran1 = rnorm(1)
r_ex = N_r*exp(alpha*ran1*log(10))

# Ytot noise
Ytot_noise = get_factor(fold_expression,r_ex)
Ytot = Ytot_org*Ytot_noise

# Atot noise
Atot_noise = get_factor(fold_expression, r_ex)
Atot = Atot_org*Atot_noise

# Rtot noise
Rtot_noise = get_factor(fold_expression, r_ex)
Rtot = Rtot_org*Rtot_noise

# Btot noise
Btot_noise = get_factor(fold_expression, r_ex)
Btot = Btot_org*Btot_noise

# Ztot noise sure??
Ztot_noise = get_factor(fold_expression, r_ex)
Ztot = Ztot_org*Ztot_noise


if (Ytot < 0){
  Ytot = 0
}
if (Atot < 0){
  Atot = 0
}
if (Ytot<Yp){
  Yp = Ytot
}

Ttot = Atot
Tm[1] = Tm[1] + Atot - Atot_org


y <- vector(len=8)
y[1:5] = Tm
y[6] = Ap
y[7] = Bp
y[8] = Yp
ystart = y
times = seq(0,total_runtime,1)
"
time_save = array(data=NA,dim=n_saves)
T0_save = array(data=NA,dim=n_saves)
T1_save  = array(data=NA,dim=n_saves)
T2_save  = array(data=NA,dim=n_saves)
T3_save  = array(data=NA,dim=n_saves)
T4_save  = array(data=NA,dim=n_saves)

Yp_save  = array(data=NA,dim=n_saves)
Bp_save  = array(data=NA,dim=n_saves)
Ap_save  = array(data=NA,dim=n_saves)
"