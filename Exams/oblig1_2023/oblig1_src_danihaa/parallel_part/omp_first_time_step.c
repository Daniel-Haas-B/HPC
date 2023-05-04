#include <omp.h>

void omp_first_time_step(int nx, int ny, double dx, double dy, double dt,
                         double **u, double **u_prev)
{
  double prefac = dt * dt / (16 * dx * dx); // dx = dy so we can use the same prefactor for both x and y.
  double u_left;
  double u_below;
  double u_right;
  double u_above;

#pragma omp parallel for private(u_left, u_below, u_right, u_above) // the private is necessary because the variables are modified in the loop!
  for (int i = 0; i < ny; i++)
  {
    for (int j = 0; j < nx; j++) // this is dumb, needs to be optimized!
    {
      if (i == 0 && j == 0)
      {
        u_left = u_prev[0][1];
        u_below = u_prev[1][0];
        u_right = u_prev[0][1];
        u_above = u_prev[1][0];
      }
      else if (i == 0 && j == nx - 1)
      {
        u_left = u_prev[0][nx - 2];
        u_below = u_prev[1][nx - 1];
        u_right = u_prev[0][nx - 2];
        u_above = u_prev[1][nx - 1];
      }
      else if (i == ny - 1 && j == 0)
      {
        u_left = u_prev[ny - 1][1];
        u_below = u_prev[ny - 2][0];
        u_right = u_prev[ny - 1][1];
        u_above = u_prev[ny - 2][0];
      }
      else if (i == ny - 1 && j == nx - 1)
      {
        u_left = u_prev[ny - 1][nx - 2];
        u_below = u_prev[ny - 2][nx - 1];
        u_right = u_prev[ny - 1][nx - 2];
        u_above = u_prev[ny - 2][nx - 1];
      }
      else if (i == 0)
      {
        u_left = u_prev[0u][j - 1];
        u_below = u_prev[1][j];
        u_right = u_prev[0][j + 1];
        u_above = u_prev[1][j];
      }
      else if (i == ny - 1)
      {
        u_left = u_prev[ny - 1][j - 1];
        u_below = u_prev[ny - 2][j];
        u_right = u_prev[ny - 1][j + 1];
        u_above = u_prev[ny - 2][j];
      }
      else if (j == 0)
      {
        u_left = u_prev[i][1];
        u_below = u_prev[i - 1][0];
        u_right = u_prev[i][1];
        u_above = u_prev[i + 1][0];
      }
      else if (j == nx - 1)
      {
        u_left = u_prev[i][nx - 2];
        u_below = u_prev[i - 1][nx - 1];
        u_right = u_prev[i][nx - 2];
        u_above = u_prev[i + 1][nx - 1];
      }
      else
      {
        u_left = u_prev[i][j - 1];
        u_below = u_prev[i - 1][j];
        u_right = u_prev[i][j + 1];
        u_above = u_prev[i + 1][j];
      }
      u[i][j] = u_prev[i][j] + prefac * (u_left + u_right + u_above + u_below - 4 * u_prev[i][j]);
    }
  }
}
