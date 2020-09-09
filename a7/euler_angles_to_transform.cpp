#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double a1 = xzx(0) * M_PI /180.0;
  double a2 = xzx(1) * M_PI /180.0;
  double a3 = xzx(2) * M_PI /180.0;

  Eigen::Affine3d A;
  Eigen::Matrix4d B, C, D;

  D <<
    1,0,0,0,
    0,cos(a1),-sin(a1),0,
    0,sin(a1),cos(a1),0,
    0,0,0,1;

  C <<
    cos(a2),-sin(a2),0,0,
    sin(a2),cos(a2),0,0,
    0,0,1,0,
    0,0,0,1;

  B <<
    1,0,0,0,
    0,cos(a3),sin(a3),0,
    0,sin(a3),cos(a3),0,
    0,0,0,1;

  A.matrix() << D * C * B;

  return A;
  /////////////////////////////////////////////////////////////////////////////
}
