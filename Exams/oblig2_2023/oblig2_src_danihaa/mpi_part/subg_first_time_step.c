#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void subg_first_time_step(int my_rank, int P, int nx, int my_ny, double dx, double dy, double dt,
                          double **my_u, double **my_u_prev)
{

  double prefac = dt * dt / (16 * dx * dx); // dx = dy so we can use the same prefactor for both x and y.
  double u_left = 0;
  double u_below = 0;
  double u_right = 0;
  double u_above = 0;

  int i_end = ((my_rank > 0) && (my_rank < P - 1)) ? my_ny + 1 : my_ny;
  if (P - 1 == 0)
  {
    i_end -= 1;
  }

  for (int i = 1; i < i_end; i++)
  {
    // left boundary
    u_left = my_u_prev[i][1];
    u_below = my_u_prev[i - 1][0];
    u_right = my_u_prev[i][1];
    u_above = my_u_prev[i + 1][0];

    my_u[i][0] = my_u_prev[i][0] + prefac * (u_left + u_right + u_above + u_below - 4 * my_u_prev[i][0]);

    // interior points
    for (int j = 1; j < nx - 1; j++)
    {
      u_left = my_u_prev[i][j - 1];
      u_below = my_u_prev[i - 1][j];
      u_right = my_u_prev[i][j + 1];
      u_above = my_u_prev[i + 1][j];

      my_u[i][j] = my_u_prev[i][j] + prefac * (u_left + u_right + u_above + u_below - 4 * my_u_prev[i][j]);
    }

    // right boundary
    u_left = my_u_prev[i][nx - 2];
    u_below = my_u_prev[i - 1][nx - 1];
    u_right = my_u_prev[i][nx - 2];
    u_above = my_u_prev[i + 1][nx - 1];

    my_u[i][nx - 1] = my_u_prev[i][nx - 1] + prefac * (u_left + u_right + u_above + u_below - 4 * my_u_prev[i][nx - 1]);
  }

  if (my_rank == 0)
  {
    // bottom left corner
    u_left = my_u_prev[0][1];
    u_below = my_u_prev[1][0];
    u_right = my_u_prev[0][1];
    u_above = my_u_prev[1][0];

    my_u[0][0] = my_u_prev[0][0] + prefac * (u_left + u_right + u_above + u_below - 4 * my_u_prev[0][0]);

    // bottom boundary
    for (int j = 1; j < nx - 1; j++)
    {
      u_left = my_u_prev[0][j - 1];
      u_below = my_u_prev[1][j];
      u_right = my_u_prev[0][j + 1];
      u_above = my_u_prev[1][j];

      my_u[0][j] = my_u_prev[0][j] + prefac * (u_left + u_right + u_above + u_below - 4 * my_u_prev[0][j]);
    }

    // bottom right corner
    u_left = my_u_prev[0][nx - 2];
    u_below = my_u_prev[1][nx - 1];
    u_right = my_u_prev[0][nx - 2];
    u_above = my_u_prev[1][nx - 1];

    my_u[0][nx - 1] = my_u_prev[0][nx - 1] + prefac * (u_left + u_right + u_above + u_below - 4 * my_u_prev[0][nx - 1]);
  }

  if (my_rank == P - 1) // notice this is not elif to include if P = 1
  {
    // top left corner
    u_left = my_u_prev[i_end][1];
    u_below = my_u_prev[i_end - 1][0];
    u_right = my_u_prev[i_end][1];
    u_above = my_u_prev[i_end - 1][0];

    my_u[i_end][0] = my_u_prev[i_end][0] + prefac * (u_left + u_right + u_above + u_below - 4 * my_u_prev[i_end][0]);

    // top boundary
    for (int j = 1; j < nx - 1; j++)
    {
      u_left = my_u_prev[i_end][j - 1];
      u_below = my_u_prev[i_end - 1][j];
      u_right = my_u_prev[i_end][j + 1];
      u_above = my_u_prev[i_end - 1][j];

      my_u[i_end][j] = my_u_prev[i_end][j] + prefac * (u_left + u_right + u_above + u_below - 4 * my_u_prev[i_end][j]);
    }

    // top right corner
    u_left = my_u_prev[i_end][nx - 2];
    u_below = my_u_prev[i_end - 1][nx - 1];
    u_right = my_u_prev[i_end][nx - 2];
    u_above = my_u_prev[i_end - 1][nx - 1];

    my_u[i_end][nx - 1] = my_u_prev[i_end][nx - 1] + prefac * (u_left + u_right + u_above + u_below - 4 * my_u_prev[i_end][nx - 1]);
  }
}
