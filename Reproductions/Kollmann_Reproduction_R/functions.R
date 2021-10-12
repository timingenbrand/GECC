"
updateT_act = function(){
  T_act[1] <<- 0
  T_act[2] <<- 0.25 * Tm[1+1] * ( 1 - ((L**1.2)/((L**1.2) + (20**1.2) ) ) ) 
  #T_act[2] <<- Tm[1+1]
  T_act[3] <<- 0.5 * Tm[2+1] * ( 1 - ((L**1.2)/((L**1.2) + (150**1.2) )) ) 
  T_act[4] <<- 0.75 * Tm[3+1] * ( 1 - ((L**1.2)/((L**1.2) + (1500**1.2) )) ) 
  T_act[5] <<- 1 * Tm[4+1] * ( 1 - ((L**1.2)/((L**1.2) + (6000**1.2) ) ) ) 
  
  T_act_sum <<- sum(T_act)
  

}

updateTm = function(id){
  term1 = 0
  term2 = 0
  if (id!=0){
    term1 = kR * Rtot * Tm[id+1-1] / (KR + Ttot) 
  }
  if (id!=4){
    term2 = kB * Bp * T_act[id+1+1] / (KB + T_act_sum)
  }
  term3 = - kR * Rtot * Tm[id+1] / (KR + Ttot)
  term4 = - kB * Bp * T_act[id+1] / (KB + T_act_sum)
  
  dtTm = term1+term2+term3+term4

  Tm[id+1] <<- Tm[id+1] + (dtTm * dt)
}

updateAp = function(){
  term1 = kA * (Atot - Ap) * T_act_sum
  term2 = -1 * kY * Ap * (Ytot - Yp)
  term3 = -1 * kB_prime * Ap * (Btot - Bp)
  #print(term1)
  #print(term2)
  #print(term3)
  dtAp = term1+term2+term3

  Ap <<- Ap + (dtAp * dt)

}

updateYp = function(){
  term1 = kY * Ap * (Ytot - Yp)
  term2 = -1* kZ * Yp * Ztot
  term3 = -1* gamY * Yp
  dtYp = term1+term2+term3
  #print(term1)
  #print(term2)
  #print(term3)
  #print(dtYp)

  Yp <<- Yp + (dtYp * dt)

}

updateBp = function(){
  term1 = kB_prime * Ap * (Btot - Bp)
  term2 = -1 * gamB * Bp
  dtBp = term1+term2
  Bp <<- Bp + (dtBp * dt)

}
"


Fun = function(t,y,parms){
  ydot <- array(data=NA,dim=8)
  
  T_act <- vector(len=5)
  T_act[1] <- 0
  T_act[2] <- 0.25 * Tm[2] * ( 1 - ((L**1.2)/((L**1.2) + (20**1.2) ) ) ) 
  T_act[3] <- 0.5 * Tm[3] * ( 1 - ((L**1.2)/((L**1.2) + (150**1.2) )) ) 
  T_act[4] <- 0.75 * Tm[4] * ( 1 - ((L**1.2)/((L**1.2) + (1500**1.2) )) ) 
  T_act[5] <- 1 * Tm[5] * ( 1 - ((L**1.2)/((L**1.2) + (6000**1.2) ) ) ) 
  
  T_act_sum <- sum(T_act)
  
  #Tm
  for (j in 1:5){
      term1 = 0
      term2 = 0
      if (j!=1){
        term1 = kR * Rtot * Tm[j-1] / (KR + Ttot) 
      }
      if (j!=5){
        term2 = kB * y[7] * T_act[j+1] / (KB + T_act_sum)
      }
      term3 = - kR * Rtot * Tm[j] / (KR + Ttot)
      term4 = - kB * y[7] * T_act[j] / (KB + T_act_sum)
      ydot[j] = term1+term2+term3+term4
  }
  
  #Ap
  term1 = kA * (Atot - y[6]) * T_act_sum
  term2 = -1 * kY * y[6] * (Ytot - y[8])
  term3 = -1 * kB_prime * y[6] * (Btot - y[7])
  ydot[6] = term1+term2+term3
  
  #Bp
  term1 = kB_prime * y[6] * (Btot - y[7])
  term2 = -1 * gamB * y[7]
  ydot[7] = term1+term2
  
  
  #Yp
  term1 = kY * y[6] * (Ytot - y[8])
  term2 = -1* kZ * y[8] * Ztot
  term3 = -1* gamY * y[8]
  ydot[8] = term1+term2+term3
  return(list(ydot))
  
}


