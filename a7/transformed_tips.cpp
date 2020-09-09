#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> > T;
  Eigen::VectorXd res = Eigen::VectorXd::Zero(3 * b.size());
  forward_kinematics(skeleton, T);

  for (int i = 0; i < b.size(); i++) {
    Eigen::VectorXd v = T[b[i]] * skeleton[b[i]].rest_T *
                        Eigen::Vector4d(skeleton[b[i]].length, 0, 0, 1);
    res[3 * i] = v[0];
    res[3 * i + 1] = v[1];
    res[3 * i + 2] = v[2];
  }

  return res;
  /////////////////////////////////////////////////////////////////////////////
}
