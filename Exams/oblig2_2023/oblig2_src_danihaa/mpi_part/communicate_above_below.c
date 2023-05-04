#include <mpi.h>
#include <stdio.h>

void communicate_above_below(int my_rank, int P, int nx, int my_ny, double **my_u)
{
    int my_above_rank = my_rank + 1;
    int my_below_rank = my_rank - 1;

    MPI_Request request[4];
    MPI_Status status[4];

    int count = 0; // count of requests sent so far (2 for each rank, 1 for each direction)

    if (my_rank > 0) // send to and recieve from below
    {
        MPI_Isend(&my_u[1][0], nx, MPI_DOUBLE, my_below_rank, 0, MPI_COMM_WORLD, &request[count++]);
        MPI_Irecv(&my_u[0][0], nx, MPI_DOUBLE, my_below_rank, 0, MPI_COMM_WORLD, &request[count++]);
    }
    if (my_rank < P - 1) // send to and recieve from above
    {
        if (my_rank != 0)
        {
            MPI_Isend(&my_u[my_ny][0], nx, MPI_DOUBLE, my_above_rank, 0, MPI_COMM_WORLD, &request[count++]);
            MPI_Irecv(&my_u[my_ny + 1][0], nx, MPI_DOUBLE, my_above_rank, 0, MPI_COMM_WORLD, &request[count++]);
        }
        else
        {
            MPI_Isend(&my_u[my_ny - 1][0], nx, MPI_DOUBLE, my_above_rank, 0, MPI_COMM_WORLD, &request[count++]);
            MPI_Irecv(&my_u[my_ny][0], nx, MPI_DOUBLE, my_above_rank, 0, MPI_COMM_WORLD, &request[count++]);
        }
    }

    MPI_Waitall(count, request, status);
}