# Potential Fold Expression Noise

#noise


get_factor = function(lambda, r_ex){
  #alpha = 0.2
  nu = 0.2
  #N_r = 0.899308 # unsure?
  N_r = 0.90
  ran2 = rnorm(1)
  
  #r_ex = N_r*exp(alpha*ran1*log(10))
  factor = (lambda*r_ex) + (nu * ran2 * sqrt(lambda*r_ex))
  return(factor)
}
"
get_factor = function(lambda){
  alpha = 0.2
  nu = 0.2
  N_r = 0.899308 # unsure?
  ran1 = rnorm(1)
  ran2 = rnorm(1)
  
  r_ex = N_r*exp(alpha*ran1*log(10))
  factor = (lambda*r_ex) + (nu * ran2 * sqrt(lambda))
  return(factor)
}
"
"
n = 100
arr = array(NA,dim=n)
for (i in 1:n){
  arr[i] = exp(0.2*rnorm(1)*log(10))
}

print(mean(arr))
print(1/mean(arr))
"