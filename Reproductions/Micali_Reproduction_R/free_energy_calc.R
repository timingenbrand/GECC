v_tsr = 0.66
v_tar = 0.34
K_off_tsr = 100
K_on_tsr = 1e6
K_off_tar = 0.03
K_on_tar = 1
gam = 0.5
N = 13

free_energy = 0
epsilon = function(c){
  tsr = v_tsr * log( (1+(c/K_off_tsr)) / (1+(c/K_on_tsr))   )
  tar = v_tar * log( (1+(c/K_off_tar)) / (1+(c/K_on_tar))   )
  
  return( (free_energy/N) - tsr - tar)
}

m = function(epsilon){
  return(  (1-epsilon) / gam   )
}



c = 1e2
m(epsilon(c)) 