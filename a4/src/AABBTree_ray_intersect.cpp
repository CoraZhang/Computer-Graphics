#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (ray_intersect_box(ray, this->box, min_t, max_t)) {
    double temp_l, temp_r;
    std::shared_ptr<Object> lson, rson;

    bool int_l = this->left && this->left->ray_intersect(ray, min_t, max_t, temp_l, lson);
    bool int_r = this->right && this->right->ray_intersect(ray, min_t, max_t, temp_r, rson);

    if (!lson && int_l) lson = left;
    if (!rson && int_r) rson = right;
    if (int_l && int_r) {
      if (temp_l < temp_r) {
        t  = temp_l;
        descendant = lson;
      }
      else {
        t = temp_r;
        descendant = rson;
      }
      return true;
    }
    if (int_l) {
      t = temp_l;
      descendant = lson;
      return true;
    }
    if (int_r) {
      t = temp_r;
      descendant = rson;
      return true;
    }
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

