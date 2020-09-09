#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double xd = ray.direction(0), yd = ray.direction(1), zd = ray.direction(2);
  double xe = ray.origin(0),ye = ray.origin(1), ze = ray.origin(2);

  double tx_min, tx_max, ty_min, ty_max, tz_min, tz_max;

  tx_min = std::min((box.min_corner(0) - xe) / xd, (box.max_corner(0) - xe) / xd);
  tx_max = std::max((box.min_corner(0) - xe) / xd, (box.max_corner(0) - xe) / xd);
  ty_min = std::min((box.min_corner(1) - ye) / yd, (box.max_corner(1) - ye) / yd);
  ty_max = std::max((box.min_corner(1) - ye) / yd, (box.max_corner(1) - ye) / yd);
  tz_min = std::min((box.min_corner(2) - ze) / zd, (box.max_corner(2) - ze) / zd);
  tz_max = std::max((box.min_corner(2) - ze) / zd, (box.max_corner(2) - ze) / zd);

  double t_min = std::max(std::max(tx_min, ty_min), tz_min);
  double t_max = std::min(std::min(tx_max, ty_max), tz_max);

  return !(t_max < t_min || (std::min(max_t, t_max) < std::max(min_t, t_min)));
  ////////////////////////////////////////////////////////////////////////////
}
