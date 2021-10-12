
update_navigation = function(){
  "Choose for every cell if it runs or tumbles"
  for (no in 1:n_bact){
    if (bact_list[[no]]@active){
      if (bact_list[[no]]@movestate == TRUE){
        move_run(no)
      }
      else if  (bact_list[[no]]@movestate == FALSE){
        move_tumble(no)
      }
    }
  }
}



move_run = function(no){
  "Bacterium run movement with constant velocity v0 and reflecting boundary
   counditions in y. Update of position and measured concentration"

  
  # propagate cell
  bact_list[[no]]@pos <<- bact_list[[no]]@pos + bact_list[[no]]@vel*dt
  
  # absorbing boundary conditions on right side of x
  if (bact_list[[no]]@pos[1] >= box_dim[1]){
    bact_list[[no]]@active <<- FALSE
    print(no)
    print("SET TO INACTIVE")
    return()
  }
  # reflective boundary conditions on left side of x
  else if (bact_list[[no]]@pos[1] < 0){
    bact_list[[no]]@vel[1] <<- (-1)*bact_list[[no]]@vel[1]
    bact_list[[no]]@theta <<- atan(bact_list[[no]]@vel[2]/bact_list[[no]]@vel[1])
    bact_list[[no]]@pos[1] <<- 0
  }
  
  # reflective boundary conditions in y
  if (bact_list[[no]]@pos[2] > box_dim[2]){
    bact_list[[no]]@vel[2] <<- (-1)*bact_list[[no]]@vel[2]
    bact_list[[no]]@theta <<- atan(bact_list[[no]]@vel[2]/bact_list[[no]]@vel[1])
    bact_list[[no]]@pos[2] <<- box_dim[2]
  }
  else if (bact_list[[no]]@pos[2] < 0){
    bact_list[[no]]@vel[2] <<- (-1)*bact_list[[no]]@vel[2]
    bact_list[[no]]@theta <<- atan(bact_list[[no]]@vel[2]/bact_list[[no]]@vel[1])
    bact_list[[no]]@pos[2] <<- 0
  }
  
  #bact_list[[no]]@cell <<- ceiling( bact_list[[no]]@pos / grid_d)
  #bact_list[[no]]@c <<- conc_grid[bact_list[[no]]@cell[1],
   #                               bact_list[[no]]@cell[2]]
  bact_list[[no]]@c <<- gradient(bact_list[[no]]@pos[1])
  
  
  # rotational diffusion
  # maybe sqrt(Dr*dt) 
  
  rot_diff_angle = rnorm(1,bact_list[[no]]@theta,std_dev)
  bact_list[[no]]@theta <<- rot_diff_angle
  bact_list[[no]]@vel <<- v0*c(cos(rot_diff_angle),sin(rot_diff_angle))
  
}


move_tumble = function(no){
  "Bacterium tumble movement with random new direction"
  
  # uniform angle distribution
  angle = as.numeric(runif(1,0,1))
  dir = 1
  if (angle > 0.5){
    dir = -1
  }
  tumble_angle = dir * sample(x=angle_sample,size=1,prob=angle_dist)
  bact_list[[no]]@theta <<- bact_list[[no]]@theta + tumble_angle
  bact_list[[no]]@vel <<- v0*c(cos(bact_list[[no]]@theta),sin(bact_list[[no]]@theta))
}