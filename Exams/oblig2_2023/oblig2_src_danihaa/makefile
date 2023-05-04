compile_serial:
	gcc-12 serial_part/serial_main.c  serial_part/allocate_2D_array.c serial_part/compute_numerical_error.c serial_part/deallocate_2D_array.c serial_part/first_time_step.c serial_part/one_regular_time_step.c serial_part/one_fast_time_step.c -o serial

run_serial:
	./serial

compile_mpi_parallel:
	mpicc mpi_part/mpi_main.c  serial_part/allocate_2D_array.c mpi_part/all_compute_numerical_error.c  serial_part/deallocate_2D_array.c mpi_part/subg_first_time_step.c  mpi_part/subg_one_fast_time_step.c mpi_part/communicate_above_below.c -o parallel_mpi

run_parallel:
	mpirun -np $(nprocs) ./parallel_mpi
