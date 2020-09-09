#include "copy_skeleton_at.h"
Skeleton copy_skeleton_at(
  const Skeleton & skeleton, 
  const Eigen::VectorXd & A)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Skeleton copy = skeleton;
  for (int i = 0; i < skeleton.size(); i++) {
    copy[i].xzx[0] = A(i * 3);
    copy[i].xzx[1] = A(i * 3 + 1);
    copy[i].xzx[2] = A(i * 3 + 2);
  }
  return copy;
  /////////////////////////////////////////////////////////////////////////////
}
