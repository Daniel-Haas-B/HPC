#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

double all_compute_numerical_error(int my_rank, int my_offset, int P, int nx, int my_ny, double dx, double dy, double t_value, double **my_u)
{
	int i, j;
	double y;
	double l_error = 0;
	double g_error = 0;
	double exact;
	double cos_i_dy;
	double diff;
	int has_neigh_below = (my_rank > 0) ? 1 : 0;

	double cos_t = cos(M_PI * t_value);

	for (i = 0; i < my_ny; i++)
	{
		cos_i_dy = cos(2.0 * M_PI * (i + my_offset) * dy);
		for (j = 0; j < nx; j++)
		{
			exact = cos(2.0 * M_PI * j * dx) * cos_i_dy * cos_t;
			diff = my_u[i + has_neigh_below][j] - exact;
			l_error += diff * diff;
		}
	}

	MPI_Allreduce(&l_error, &g_error, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	return sqrt(dx * dy * g_error);
}
