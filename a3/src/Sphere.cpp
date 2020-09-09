#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double A = ray.direction.dot(ray.direction);
  double B = 2 * (ray.origin - center).dot(ray.direction);
  double C = (ray.origin - center).dot(ray.origin - center) - pow(radius, 2.0);

  double delta = B * B - 4 * A * C;
  if (delta < 0) {
    return false;
  }

  double t1 = (-B - std::sqrt(delta)) / (2.0 * A);
  double t2 = (-B + std::sqrt(delta)) / (2.0 * A);

  if (t2 < min_t) {
    return false;
  }

  if (t1 < min_t) {
    t = t2;
  } else {
    t = t1;
  }

  Eigen::Vector3d p = ray.origin + t * ray.direction;
  n = (p - center).normalized();

  return true;

  ////////////////////////////////////////////////////////////////////////////
}
