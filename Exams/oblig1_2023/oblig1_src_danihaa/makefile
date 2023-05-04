compile_serial:
	gcc-12 serial_part/serial_main.c  serial_part/allocate_2D_array.c serial_part/compute_numerical_error.c serial_part/deallocate_2D_array.c serial_part/first_time_step.c serial_part/one_regular_time_step.c serial_part/one_fast_time_step.c -o serial

run_serial:
	./serial

compile_parallel:
	gcc-12 parallel_part/para_main.c  serial_part/allocate_2D_array.c parallel_part/omp_compute_numerical_error.c serial_part/deallocate_2D_array.c parallel_part/omp_first_time_step.c parallel_part/omp_one_regular_time_step.c parallel_part/omp_one_fast_time_step.c -fopenmp -o parallel

run_parallel:
	./parallel