#include "fast_mass_springs_step_dense.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::MatrixXd & M,
  const Eigen::MatrixXd & A,
  const Eigen::MatrixXd & C,
  const Eigen::LLT<Eigen::MatrixXd> & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::MatrixXd y = 1.0 / (delta_t * delta_t) * M * (2 * Ucur - Uprev) + fext;
  y += (1e10 * C.transpose() * C) * V;

  Unext = Ucur;

  for (int iter = 0;iter < 50;iter++) {
    Eigen::MatrixXd d = Eigen::MatrixXd::Zero(E.rows(), 3);
    for (int i = 0; i < E.rows(); i++) {
      d.row(i) = (A * Unext).row(i) / (A * Unext).row(i).norm() * r(i);
    }
    const Eigen::MatrixXd l = k * A.transpose() * d + y;
    Unext = prefactorization.solve(l);
  }
  //////////////////////////////////////////////////////////////////////////////
}
