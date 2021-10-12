# Drift velocity analysis
#library(ggplot2)

id = 0
n_bact = 25
dt = 0.01
steps = 5e6
time = steps*dt
grad_type = 0

save_intervall = 10

n_saves = time/(dt*save_intervall)

steps = time/dt

run_name = sprintf("run_id%s_%s_%s_%s", id, grad_type, n_bact, time)
data_list = list()
data_list <- vector(mode = "list", length = n_bact)
#data_full = matrix(data=0,nrow=(n_saves*n_bact),ncol=11)

for (no in 1:n_bact){
  filename = sprintf("results/%s/bact_%s.csv",run_name,no)
  help = read.table(filename,header=TRUE,sep=",")
  data_list[[no]] = help
  #data_full[((1+(no-1)*n_saves):(1+no*n_saves)),] = read.table(filename,header=TRUE,sep=",")
}

avg_vel = 0
for (no in 1:n_bact){
  vel = sum(data_list[[no]][,4])
  vel = vel / n_saves
  avg_vel = avg_vel + vel
}
avg_vel = avg_vel / n_bact
print(avg_vel)
### trajectories
if(1){
  no = 1
  time_list = data_list[[no]][,1]
  velx_list = data_list[[no]][,4]
  vely_list = data_list[[no]][,5]
  posx_list = data_list[[no]][,2]
  posy_list = data_list[[no]][,3]
  Yp_list = data_list[[no]][,6]
  A_list = data_list[[no]][,7]
  m_list = data_list[[no]][,8]
  fed_list = data_list[[no]][,9]
  c_list = data_list[[no]][,10]
  Ncw_list = data_list[[no]][,11]
  active_list = data_list[[no]][,12]

  plot(posx_list,posy_list,type="l",lwd=0.1, main="lambda = 0.75 (1/mm)",xlim=c(0,3e4),ylim=c(0,2e4))
  poscrit = 11600
  x = c(poscrit,poscrit)
  y = c(0,12)
  #lines(x,y,lwd=0.1,col="red")
  #lines(x,y)
  for (i in 2:n_bact){
    no = i
    #time_list = data_list[[no]][,1]
    posx_list = data_list[[no]][,2]
    posy_list = data_list[[no]][,3]
    #m_list = data_list[[no]][,8]
    lines(posx_list,posy_list,lwd=0.1)
  }
  #points(c(2500),c(10000),cex=1,col="red",pch=19)
  # no time posx
  # 1 20.6 12.6
  # 2 26.2 12.2
  # 3 23.3 11.6
}


### concentration vs velx
if(1){
  max_c = 10
  c_binwidth = 0.05
  c_bin_no = (max_c / c_binwidth)+1
  c_bins = seq(0, max_c, c_binwidth)
  velx_bins = array(data=0, dim=(c_bin_no))
  count_bins = array(data=0,dim=c(c_bin_no))
  
  
  for (i in 1:n_bact){
    c_list = data_list[[i]][,10]
    velx_list = data_list[[i]][,4]
    for (j in 1:n_saves){
      c_bin = floor(c_list[j]/c_binwidth)
      if (c_bin < c_bin_no){
        velx_bins[c_bin] = velx_bins[posx_bin] + velx_list[j]
        count_bins[c_bin] = count_bins[c_bin] + 1
      }
    }
  }
  velx_bins = velx_bins / count_bins
  plot(c_bins,velx_bins,type="l",log="x")
}

### posx vs velx
if(1){
  max_posx = 15000
  posx_binwidth = 20
  posx_bin_no = (max_posx / posx_binwidth)+1
  posx_bins = seq(0, max_posx, posx_binwidth)
  velx_bins = array(data=0, dim=(posx_bin_no))
  count_bins = array(data=0,dim=c(posx_bin_no))
  
  
  for (i in 1:n_bact){
    posx_list = data_list[[i]][,2]
    velx_list = data_list[[i]][,4]
    for (j in 1:n_saves){
      posx_bin = floor(posx_list[j]/posx_binwidth)
      if (!is.na(posx_bin)){
        if (posx_bin < posx_bin_no){
          velx_bins[posx_bin] =velx_bins[posx_bin] + velx_list[j]
          count_bins[posx_bin] = count_bins[posx_bin] + 1
        }
      }
    }
  }
  velx_bins = velx_bins / count_bins
  c_bins = gradient(posx_bins)
  min_count = 100
  #plot(posx_bins[count_bins>min_count],velx_bins[count_bins>min_count],type="l")

  plot(c_bins[count_bins>min_count],velx_bins[count_bins>min_count],type="l", log="x", main="lambda = 0.75(1/mm), min 100 counts",
   xlab="Concentration [mM]", ylab="Velocity in x [µm/s]",ylim=c(0,3))
  lines(c(min(c_bins),max(c_bins)), c(0,0), col="red")
  lines(c(0.1,0.1), c(-1,6), col="red")
}

### test
min = 5000
max = 5500
vel = 0
count = 0
for (i in 1:n_bact){
  posx_list = data_list[[i]][,2]
  velx_list = data_list[[i]][,4]
  for (j in 1:n_saves){
    if (posx_list[j] < max){
      if(posx_list[j] >= min){
        vel = vel + velx_list[j]
        count = count + 1
      }
    }
  }
}
vel = vel / count
print(vel)
print(count)




if(1){
# Average X-Position over time
max = time
bin_width = 1
n_bins = (max/bin_width)+1

time_bins = seq(0,max,bin_width)
counter = array(data=0,dim=n_bins)
posx_bins = array(data=0,dim=n_bins)
for (no in 1:n_bact){
  for (sav in 1:n_saves){
    # determine bin using time
    bin = ceiling((data_list[[no]][sav,1] / bin_width))
    
    
    posx_bins[bin] = posx_bins[bin] + data_list[[no]][sav,2]
    counter[bin] = counter[bin] + 1
  }
}
#plot(data_list[[2]][,2],data_list[[2]][,4])
counter = counter + 1
posx_bins = posx_bins / counter
relative_counter = counter / sum(counter)

#19448
plot(time_bins,posx_bins,xlab="Time [s]",ylab="Avg Position in X [um]", type="l", main="E. Coli biased random walk")
#lines(c_bins,10*relative_counter, col="steelblue")
}
