
save_data = function(){
  # Saving data after every save_intervall steps
  for (no in 1:n_bact){
  save_matrix[no,save_no,1] <<- run_time
  save_matrix[no,save_no,2:3] <<- bact_list[[no]]@pos
  save_matrix[no,save_no,4:5] <<- bact_list[[no]]@vel
  save_matrix[no,save_no,6] <<- bact_list[[no]]@Yp
  save_matrix[no,save_no,7] <<- bact_list[[no]]@A
  save_matrix[no,save_no,8] <<- bact_list[[no]]@m
  save_matrix[no,save_no,9] <<- bact_list[[no]]@fed
  save_matrix[no,save_no,10] <<- bact_list[[no]]@c
  save_matrix[no,save_no,11] <<- bact_list[[no]]@Ncw
  save_matrix[no,save_no,12] <<- bact_list[[no]]@active
  }
  
}


write_output = function(){
  dir_name = sprintf("./results/run_id%s_%s_%s_%s_%s", run_id, n_bact, total_runtime,
                     grad_x0*100000,M)
  dir.create(dir_name)
  
  # write data
  for (no in 1:n_bact){
    filename = sprintf("%s/bact_%s.csv", dir_name,no+n_bact*namecount)
    write.csv(save_matrix[no,,],filename,row.names =FALSE)
  }


}


