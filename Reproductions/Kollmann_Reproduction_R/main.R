library("deSolve")

source("parameters.R")
source("functions.R")
source("noise.R")

#set.seed(15)
fo_ex = c(0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 2, 3, 4, 5 )
for (k in 1:10){
  save_matrix = array(data=NA,dim=c(n_bact,8))
  fold_expression = fo_ex[k]
  print(fold_expression)
  for (i in 1:n_bact){
   
    source("parameters.R")
  
    source("setup.R")
    
    out <- lsoda(ystart, times, Fun)
    end_y = out[total_runtime+1,2:9]
    source("save.R")
    #plot(out)
    
    #Fun(1,ystart,0)
    
    
    #currTime = 0
    #n_output = 0
    "
    for (j in 1:steps){
      
      currTime = currTime + dt
      n_output = n_output+1
      updateT_act()
      for (k in 0:4){
        updateTm(k)}
      updateAp()
      updateYp()
      updateBp()
      
      
      
    }"
    
    #print(sprintf("%s %s %s", i, Ytot, end_y[8]))
    
  
    
  }
  filename = sprintf("results_%s_%s.csv",n_bact, fold_expression)
  write.csv(save_matrix,filename,row.names =FALSE)
  print("FINISHED")
}