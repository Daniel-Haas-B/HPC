#include <math.h>

double compute_numerical_error(int nx, int ny, double dx, double dy,
                               double t_value, double **u)
{
  double error = 0.0;
  double x_j;
  double y_i;
  double diff;
  for (int i = 0; i < ny; i++)
  {
    for (int j = 0; j < nx; j++)
    {
      x_j = j * dx;
      y_i = i * dy;
      diff = cos(2 * M_PI * x_j) * cos(2 * M_PI * y_i) * cos(M_PI * t_value) - u[i][j];
      error += diff * diff;
    }
  }
  return sqrt(dx * dy * error);
}
