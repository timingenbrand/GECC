gradient = function(x){
  concentration = grad_x1*exp(grad_x0*(x+grad_x2)) + grad_x3
  return (concentration)
}
# Define E. Coli class here
setClass("bacterium",slots=list(id="numeric", 
                                pos="numeric", vel="numeric",
                                theta = "numeric",
                                c="numeric", 
                                A = "numeric", m="numeric",
                                Yp="numeric", motorstates="array",
                                movestate="logical", active="logical",
                                fed="numeric", Ncw="numeric"))


# Create all bacteria
bact_list = list()
for (no in 1:n_bact){
  pos = c((2.5/30)*box_dim[1] , 0.5*box_dim[2])
  #pos = c((0/30)*box_dim[1] , 0.5*box_dim[2])
  
  #pos = c(((12+no*1)/30)*box_dim[1], 0.5*box_dim[2])
  #c = conc_grid[cell[1],cell[2]]
  c = gradient(pos[1])
  theta = runif(1,0,2*pi)
  #theta = 0
  vel= v0*c(cos(theta),sin(theta))
  m = 1.9
  #m = 4.58
  A = 0
  active=TRUE
  motorstates = array(data=TRUE,dim=M)

  bacteria = new("bacterium", id = no, pos = pos, vel = vel, theta = theta,
                 c = c, A=A, m=m, 
                 Yp=0, motorstates=motorstates, movestate=TRUE, active=active,
                 fed=0, Ncw=0)

  bact_list[no] = bacteria
  rm(bacteria)
  
}
