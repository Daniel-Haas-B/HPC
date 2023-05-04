#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void one_regular_time_step(int nx, int ny, double dx, double dy, double dt,
                           double **u_new, double **u, double **u_prev)
{
  double u_left;
  double u_below;
  double u_right;
  double u_above;
  double prefac = dt * dt / (8 * dx * dx); // dx = dy so we can use the same prefactor for both x and y.

  for (int i = 0; i < ny; i++)
  {
    for (int j = 0; j < nx; j++) // this is dumb, needs to be optimized!
    {
      if (i == 0 && j == 0)
      {
        u_left = u[0][1];
        u_below = u[1][0];
        u_right = u[0][1];
        u_above = u[1][0];
      }
      else if (i == 0 && j == nx - 1)
      {
        u_left = u[0][nx - 2];
        u_below = u[1][nx - 1];
        u_right = u[0][nx - 2];
        u_above = u[1][nx - 1];
      }
      else if (i == ny - 1 && j == 0)
      {
        u_left = u[ny - 1][1];
        u_below = u[ny - 2][0];
        u_right = u[ny - 1][1];
        u_above = u[ny - 2][0];
      }
      else if (i == ny - 1 && j == nx - 1)
      {
        u_left = u[ny - 1][nx - 2];
        u_below = u[ny - 2][nx - 1];
        u_right = u[ny - 1][nx - 2];
        u_above = u[ny - 2][nx - 1];
      }
      else if (i == 0)
      {
        u_left = u[0][j - 1];
        u_below = u[1][j];
        u_right = u[0][j + 1];
        u_above = u[1][j];
      }
      else if (i == ny - 1)
      {
        u_left = u[ny - 1][j - 1];
        u_below = u[ny - 2][j];
        u_right = u[ny - 1][j + 1];
        u_above = u[ny - 2][j];
      }
      else if (j == 0)
      {
        u_left = u[i][1];
        u_below = u[i - 1][0];
        u_right = u[i][1];
        u_above = u[i + 1][0];
      }
      else if (j == nx - 1)
      {
        u_left = u[i][nx - 2];
        u_below = u[i - 1][nx - 1];
        u_right = u[i][nx - 2];
        u_above = u[i + 1][nx - 1];
      }
      else
      {
        u_left = u[i][j - 1];
        u_below = u[i - 1][j];
        u_right = u[i][j + 1];
        u_above = u[i + 1][j];
      }

      u_new[i][j] = 2 * u[i][j] - u_prev[i][j] + prefac * (u_left + u_right + u_above + u_below - 4 * u[i][j]);
    }
  }
}
