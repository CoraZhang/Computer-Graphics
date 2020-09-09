#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);
  Eigen::VectorXd p_t = transformed_tips(skeleton, b);
  const double eps = 1e-6;

  Eigen::VectorXd O = transformed_tips(skeleton, b);
  for (int i = 0; i < skeleton.size(); i++){
    for (int j = 0; j < 3; j++){
      Skeleton t = skeleton;
      t[i].xzx(j) += eps;
      Eigen::VectorXd p = transformed_tips(t, b);
      J.col(i * 3 + j) = (p - p_t) / eps;
    }
  }

  /////////////////////////////////////////////////////////////////////////////
}
