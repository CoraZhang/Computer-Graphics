#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Eigen::Vector3d A = std::get<0>(corners);
  Eigen::Vector3d A, B, C;
  std::tie(A, B, C) = corners;
  Eigen::Vector3d AB = B - A;
  Eigen::Vector3d AC = C - A;

  Eigen::Vector3d normal = AB.cross(AC);
  
  if (normal.dot(ray.direction) == 0) {
    return false;
  }

  t = (A - ray.origin).dot(normal) / (ray.direction.dot(normal));
  if (t < min_t) {
    return false;
  }

  Eigen::Vector3d OA = A - ray.origin;

  double a = -AB[0];
  double b = -AB[1];
  double c = -AB[2];

  double d = -AC[0];
  double e = -AC[1];
  double f = -AC[2];

  double g = ray.direction[0];
  double h = ray.direction[1];
  double i = ray.direction[2];

  double j = OA[0];
  double k = OA[1];
  double l = OA[2];

  double eihf = e * i - h * f;
  double gfdi = g * f - d * i;
  double dheg = d * h - e * g;
  double akjb = a * k - j * b;
  double jcal = j * c - a * l;
  double blkc = b * l - k * c;
  double M = a * eihf + b * gfdi + c * dheg;

  double gamma = (i * akjb +h * jcal + g * blkc) / M;
  if ((gamma < 0) || (gamma > 1)) {
    return false;
  }

  double beta = (j * eihf + k * gfdi + l * dheg) / M;
  if ((beta < 0) || (beta + gamma > 1)) {
    return false;
  }

  n = normal.normalized();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}


