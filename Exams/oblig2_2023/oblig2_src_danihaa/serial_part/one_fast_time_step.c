#include <stdio.h>
#include <stdlib.h>

void one_fast_time_step(int nx, int ny, double dx, double dy, double dt,
                        double **u_new, double **u, double **u_prev)
{
  double u_left;
  double u_below;
  double u_right;
  double u_above;
  double prefac = dt * dt / (8 * dx * dx); // dx = dy so we can use the same prefactor for both x and y.

  // inner points (i.e. not on the boundary)
  for (int i = 1; i < ny - 1; i++)
  {
    for (int j = 1; j < nx - 1; j++)
    {
      u_left = u[i][j - 1];
      u_below = u[i - 1][j];
      u_right = u[i][j + 1];
      u_above = u[i + 1][j];

      u_new[i][j] = 2 * u[i][j] - u_prev[i][j] + prefac * (u_left + u_right + u_above + u_below - 4 * u[i][j]);
    }
  }

  // boundary points

  // left and right boundary

  // left boundary (i.e. j = 0 and i != 0 and i != ny - 1)
  for (int i = 1; i < ny - 1; i++)
  {
    u_left = u[i][1];
    u_below = u[i - 1][0];
    u_right = u[i][1];
    u_above = u[i + 1][0];

    u_new[i][0] = 2 * u[i][0] - u_prev[i][0] + prefac * (u_left + u_right + u_above + u_below - 4 * u[i][0]);
  }

  // right boundary (i.e. j = nx - 1 and i != 0 and i != ny - 1)
  for (int i = 1; i < ny - 1; i++)
  {
    u_left = u[i][nx - 2];
    u_below = u[i - 1][nx - 1];
    u_right = u[i][nx - 2];
    u_above = u[i + 1][nx - 1];

    u_new[i][nx - 1] = 2 * u[i][nx - 1] - u_prev[i][nx - 1] + prefac * (u_left + u_right + u_above + u_below - 4 * u[i][nx - 1]);
  }

  // top and bottom boundary

  // top boundary (i.e. i = 0 and j != 0 and j != nx - 1)
  for (int j = 1; j < nx - 1; j++)
  {
    u_left = u[0][j - 1];
    u_below = u[1][j];
    u_right = u[0][j + 1];
    u_above = u[1][j];

    u_new[0][j] = 2 * u[0][j] - u_prev[0][j] + prefac * (u_left + u_right + u_above + u_below - 4 * u[0][j]);
  }

  // bottom boundary (i.e. i = ny - 1 and j != 0 and j != nx - 1)
  for (int j = 1; j < nx - 1; j++)
  {
    u_left = u[ny - 1][j - 1];
    u_below = u[ny - 2][j];
    u_right = u[ny - 1][j + 1];
    u_above = u[ny - 2][j];

    u_new[ny - 1][j] = 2 * u[ny - 1][j] - u_prev[ny - 1][j] + prefac * (u_left + u_right + u_above + u_below - 4 * u[ny - 1][j]);
  }

  // corner points
  // top left corner (i.e. i = 0 and j = 0)
  u_left = u[0][1];
  u_below = u[1][0];
  u_right = u[0][1];
  u_above = u[1][0];

  u_new[0][0] = 2 * u[0][0] - u_prev[0][0] + prefac * (u_left + u_right + u_above + u_below - 4 * u[0][0]);

  // top right corner (i.e. i = 0 and j = nx - 1)
  u_left = u[0][nx - 2];
  u_below = u[1][nx - 1];
  u_right = u[0][nx - 2];
  u_above = u[1][nx - 1];

  u_new[0][nx - 1] = 2 * u[0][nx - 1] - u_prev[0][nx - 1] + prefac * (u_left + u_right + u_above + u_below - 4 * u[0][nx - 1]);

  // bottom left corner (i.e. i = ny - 1 and j = 0)
  u_left = u[ny - 1][1];
  u_below = u[ny - 2][0];
  u_right = u[ny - 1][1];
  u_above = u[ny - 2][0];

  u_new[ny - 1][0] = 2 * u[ny - 1][0] - u_prev[ny - 1][0] + prefac * (u_left + u_right + u_above + u_below - 4 * u[ny - 1][0]);

  // bottom right corner (i.e. i = ny - 1 and j = nx - 1)
  u_left = u[ny - 1][nx - 2];
  u_below = u[ny - 2][nx - 1];
  u_right = u[ny - 1][nx - 2];
  u_above = u[ny - 2][nx - 1];

  u_new[ny - 1][nx - 1] = 2 * u[ny - 1][nx - 1] - u_prev[ny - 1][nx - 1] + prefac * (u_left + u_right + u_above + u_below - 4 * u[ny - 1][nx - 1]);
}
