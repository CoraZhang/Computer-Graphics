#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double s = max_step;
  Eigen::VectorXd t = z - s * dz;
  proj_z(t);

  while (f(t) > f(z)) {
    s *= 0.5;
    t = z - s * dz;
    proj_z(t);

    if (t == z) {
      return 0.;
    }
  }

  return s;
  /////////////////////////////////////////////////////////////////////////////
}
