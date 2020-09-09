#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  double d_x, d_y, d_z;

  d_x = std::max(std::max(box.min_corner[0] - query(0), 0.), query(0) - box.max_corner[0]);
  d_y = std::max(std::max(box.min_corner[1] - query(1), 0.), query(1) - box.max_corner[1]);
  d_z = std::max(std::max(box.min_corner[2] - query(2), 0.), query(2) - box.max_corner[2]);

  return d_x * d_x + d_y * d_y + d_z * d_z;
  ////////////////////////////////////////////////////////////////////////////
}
