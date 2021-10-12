

update_activity = function(){
  for (no in 1:n_bact){

    # calcuate epsilon(m)
    e_of_m = 1 - (gam * bact_list[[no]]@m)
    
    #calculate contributions of both receptor types
    tsr = v_tsr * log( (1+(bact_list[[no]]@c/K_off_tsr)) / 
                         (1+(bact_list[[no]]@c/K_on_tsr)), base=exp(1) )
    
    tar = v_tar * log( (1+(bact_list[[no]]@c/K_off_tar)) / 
                         (1+(bact_list[[no]]@c/K_on_tar)), base = exp(1)  )
    
    # calculate free energy difference and activity
    free_energy_diff = n_recep*(e_of_m + tsr + tar)
    bact_list[[no]]@fed <<- free_energy_diff
    #print(free_energy_diff)
    bact_list[[no]]@A <<- 1 / (1 + exp(free_energy_diff)) 
  }  

}


update_adaptation = function(){
  # update methylation level m according to algebraic equation
  for (no in 1:n_bact){
      #print(bact_list[[no]]@m)
      bact_list[[no]]@m <<- bact_list[[no]]@m + 
        ( ( (gam_R * (1-(bact_list[[no]]@A)))
           - (gam_B * (bact_list[[no]]@A**3)) ) * dt )
     #bact_list[[no]]@m <<- bact_list[[no]]@m + 
      #( ( (gam_R * (1-(bact_list[[no]]@A)))
       #   - (gam_B * (bact_list[[no]]@A)) ) * dt )
     
      if (bact_list[[no]]@m < 0){
        bact_list[[no]]@m <<- 0
      }
      else if(bact_list[[no]]@m > 8){
        bact_list[[no]]@m <<- 8
      }
  }
  
}


update_flagella = function(){
  for (no in 1:n_bact){
    if (bact_list[[no]]@active){
    # update Yp concentration
    nominator = kY*(bact_list[[no]]@A)*Y_tot
    denominator = kY*(bact_list[[no]]@A) + kZ * Z_tot + gam_Y
    bact_list[[no]]@Yp <<- nominator / denominator      
    run = TRUE  

    for (motor in 1:M){  
      # calculate switch rate to other movestate
      if (bact_list[[no]]@motorstates[motor] == TRUE){ 
        # if currently running, calculate switch rate to tumble
        switch_rate = (1/t0)*(exp(-1* (20 - ( (40*bact_list[[no]]@Yp) /
                                             (bact_list[[no]]@Yp+3.06) ) ) ))
        }
      else if (bact_list[[no]]@motorstates[motor] == FALSE){
        # if currently tumbling, calculate switch rate to run
        switch_rate = (1/t0)* exp(+1* (20 - ( (40*bact_list[[no]]@Yp) /
                                                (bact_list[[no]]@Yp+3.06) ) ) )
        
      }
      
      
      # calculate switch probability from rate
      
      switch_prob = switch_rate * dt
      #print(switch_prob)
      if (switch_prob>=1){
        print("Switchprobe larger than 1 ")
        print(switch_prob)
      } 

      if (runif(1) < switch_prob){ # check if current motor switches
        if (bact_list[[no]]@motorstates[motor]){ # if current motor is running(ccw)
          bact_list[[no]]@Ncw <<- bact_list[[no]]@Ncw + 1
        }
        else{ # if current motor is tumbling (cw)
          bact_list[[no]]@Ncw <<- bact_list[[no]]@Ncw - 1
        }
        # change state of current motor
        bact_list[[no]]@motorstates[motor] <<- !bact_list[[no]]@motorstates[motor]

      }
      
      
      # if all motors are running (ccw), run variable stays true and movestate 
      # of whole cell is also run (=TRUE)
      if (bact_list[[no]]@motorstates[motor] == FALSE){
        run = FALSE
      }
      
    }
    
    bact_list[[no]]@movestate <<- run
      
    }
  }  
}