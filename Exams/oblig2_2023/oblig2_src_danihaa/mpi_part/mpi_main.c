#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "../serial_part/functions.h"
#include <mpi.h>
#include <assert.h>

#define Pi M_PI

int main(int nargs, char **args)
{
  int nx = 1001, ny = 1001;
  double T = 2.0; // default values
  int i, j;
  double dx, dy, dt, t;
  double **my_u, **my_u_new, **my_u_prev, **my_tmp_ptr; // private to each process, and signify the local part of the global array
  int my_offset;                                        // offset of the local part of the global array
  int my_ny;                                            // number of rows in the local part of the global array
  int my_rank;                                          // rank of the process
  int P;                                                // number of processes
  int has_neigh_below, has_neigh_above;                 // flags to indicate if the process has a neighbor below or above

  MPI_Init(&nargs, &args);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // returns the rank of the calling process
  MPI_Comm_size(MPI_COMM_WORLD, &P);       // returns the size of the group associated with a communicator

  assert(ny / P > 0); // make sure that the number of rows is divisible by the number of processes

  if (my_rank == 0)
  {
    if (nargs > 1) // if a new value of nx is provided on the command line
      nx = ny = atoi(args[1]);
    if (nargs > 2) // if a new value of T is provided on the command line
      T = atof(args[2]);
  }

  // let process 0 broadcast values of nx, ny and T to all other processes
  // args: address of the data, number of elements, type of the elements, rank of the process that broadcasts the data, communicator
  MPI_Bcast(&nx, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&ny, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&T, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  has_neigh_below = (my_rank > 0) ? 1 : 0;      // process w rank 0 is responsible for the bottom stripe, so it has no neighbor below
  has_neigh_above = (my_rank < P - 1) ? 1 : 0;  // process w rank P − 1 is responsible for the top stripe, so it has no neighbor above
  my_offset = (my_rank * ny) / P;               // where the process' section starts in the global array
  my_ny = ((my_rank + 1) * ny) / P - my_offset; // # of rows in the section of the global array that is assigned to the process

  // allocate memory for the local part of the global array. remember to add space for the ghost rows
  allocate_2D_array(&my_u, nx, (my_ny + has_neigh_below + has_neigh_above));
  allocate_2D_array(&my_u_new, nx, (my_ny + has_neigh_below + has_neigh_above));
  allocate_2D_array(&my_u_prev, nx, (my_ny + has_neigh_below + has_neigh_above));

  dx = 1.0 / (nx - 1);
  dy = 1.0 / (ny - 1);
  dt = 2.0 * dx; // maximum value allowed for the time step size

  // start timing
  MPI_Barrier(MPI_COMM_WORLD);     // impotant to ensnure correct timing else the processes can start at different times
  double start_time = MPI_Wtime(); // MPI way of geting wall time. Important because just using clock will give us the sum of cpu times

  // set initial condition
  for (i = 0; i < my_ny; i++)
    for (j = 0; j < nx; j++)
      my_u_prev[i + has_neigh_below][j] = cos(2.0 * Pi * j * dx) * cos(2.0 * Pi * (i + my_offset) * dy);

  communicate_above_below(my_rank, P, nx, my_ny, my_u_prev); // communicate ghost rows to neighbors
  subg_first_time_step(my_rank, P, nx, my_ny, dx, dy, dt, my_u, my_u_prev);

  // compute the remaining time steps
  t = dt;
  while (t < T)
  {
    t += dt;
    communicate_above_below(my_rank, P, nx, my_ny, my_u);
    subg_one_fast_time_step(my_rank, P, nx, my_ny, dx, dy, dt, my_u_new, my_u, my_u_prev);

    /* pointer swaps */
    my_tmp_ptr = my_u_prev;
    my_u_prev = my_u;
    my_u = my_u_new;
    my_u_new = my_tmp_ptr;
  }

  printf("my_rank=%d, nx=%d, my_ny=%d, T=%g, dt=%g, error=%e\n", my_rank, nx, my_ny, t, dt,
         all_compute_numerical_error(my_rank, my_offset, P, nx, my_ny, dx, dy, t, my_u));

  //  stop timing
  MPI_Barrier(MPI_COMM_WORLD); // again, important to wait for all processes to reach this point.
  double end_time = MPI_Wtime();

  if (my_rank == 0)
    printf("Elapsed time: %g s \n", end_time - start_time);

  // deallocate arrays my_u_new, my_u, my_u_prev
  deallocate_2D_array(my_u_new);
  deallocate_2D_array(my_u);
  deallocate_2D_array(my_u_prev);

  MPI_Finalize();

  return 0;
}