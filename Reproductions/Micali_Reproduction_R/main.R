# Simulation of Escherichica Coli Bacterium
# import functions
#set.seed(8)
source("movement.R")
source("signaling.R")
source("output.R")
source("parameters.R")
source("bacteria_setup.R")

starttime = Sys.time()
args = commandArgs(trailingOnly=TRUE)
namecount = as.numeric(args[1])
namecount = 0
save_matrix = array(data=NA,dim=c(n_bact,n_saves,12))
if (exists("run_id")){
  run_id = run_id + 1
} else { run_id = 0}

run_time = 0
save_counter = 0
save_no = 0
switch_counter = 0

std_dev = sqrt(Dr*dt)
for (step in 1:steps){

  
  # Signaling
  update_activity()
  update_adaptation()
  update_flagella()
  
  #Navigation
  #update_navigation()
  
  # Saving
  run_time = run_time + dt
  save_counter = save_counter + 1
  if (save_counter %% save_intervall == 0){
    save_no = save_no + 1
    save_data()
  }

}

write_output()
endtime = Sys.time()
endtime-starttime

sprintf("FINISHED with run id %s",run_id)

