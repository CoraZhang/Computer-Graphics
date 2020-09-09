#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  U.resize(V.rows(), 3);
  
  for (int i = 0; i < V.rows(); i++) {
      Eigen::Vector4d base(0, 0, 0, 0);
      for (int j = 0; j < skeleton.size(); j++) {
          if (skeleton[j].weight_index != -1){
              Eigen::Vector4d rest = Eigen::Vector4d(V(i, 0), V(i, 1), V(i, 2), 1);
              base += W(i, skeleton[j].weight_index) * (T[j] * rest);
          }
      }
      U(i, 0) = base.x();
      U(i, 1) = base.y();
      U(i, 2) = base.z();
  }
  /////////////////////////////////////////////////////////////////////////////
}
