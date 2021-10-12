
# Initializing gradient and attractant grid
box_dim = c(30000,20000)
# defines grid resolution
grid_dim = c(300000,1) # don't need resolution in y because its constant
grid_d  = box_dim/grid_dim

grad_type = 0
# define gradient function 
if (grad_type==0)  # exponential
  gradient = function(x){
    grad_x0 = 0.75e-3
    grad_x1 = 0.1
    grad_x2 = -2500
    grad_x3 = 0
    concentration = grad_x1*exp(grad_x0*(x+grad_x2)) + grad_x3
    return (concentration)
  }
if (grad_type==1)  # linear
  gradient = function(x){
    grad_x0 = 2e-3
    grad_x1 = 0.1
    concentration = grad_x0 * x + grad_x1
  }




x_lin = seq(grid_d[1], box_dim[1], grid_d[1])
#y_lin = seq(grid_d[2], box_dim[2], grid_d[2])

# define gradient-grid 
# currently a gradient in x-direction and constant in y
conc_grid = matrix(x_lin,nrow=grid_dim[1],ncol=grid_dim[2])
conc_grid = gradient(conc_grid)



# delete unneeded variables to clear ram
#rm(grad_x0,grad_x1,grad_x2,grad_x3,grad_type,x_lin)
