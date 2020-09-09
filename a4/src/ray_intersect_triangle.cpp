#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::RowVector3d BA = A - B, CA = A - C;

  double a = BA[0], b = BA[1], c = BA[2];
  double d = CA[0], e = CA[1], f = CA[2];
  double g = ray.direction[0], h = ray.direction[1], i = ray.direction[2];
  double j = A[0] - ray.origin[0], k = A[1] - ray.origin[1], l = A[2] - ray.origin[2];

  double con = a*(e*i-h*f) + b*(g*f-d*i) + c*(d*h-e*g);
  double beta = (j*(e*i-h*f) + k*(g*f-d*i) + l*(d*h-e*g)) / con;
  double gamma = (i*(a*k -j*b) + h*(j*c-a*l) + g*(b*l-k*c)) / con;

  t = -(f*(a*k-j*b) + e*(j*c-a*l) + d*(b*l-k*c)) / con;
  if (t < min_t || t > max_t) return false;
  return !(gamma < 0 || beta < 0 || gamma > 1 || beta > 1 || gamma + beta > 1);
  ////////////////////////////////////////////////////////////////////////////
}

