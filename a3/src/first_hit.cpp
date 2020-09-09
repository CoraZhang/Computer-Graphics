#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool res = false;
  t = -1;

  double tmp_t;
  Eigen::Vector3d tmp_n;

  for (int i = 0; i < objects.size(); i++) {
    auto& x = objects[i];
    if (x->intersect(ray, min_t, tmp_t, tmp_n)) {
      res = true;
      if (t == -1 || t > tmp_t) {
        t = tmp_t;
        n = tmp_n;
        hit_id = i;
      }
    }
  }

  return res;
  ////////////////////////////////////////////////////////////////////////////
}
