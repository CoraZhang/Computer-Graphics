#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  double u = -(camera.width * 0.5) + (camera.width * (j + 0.5) / width);
  double v = (camera.height * 0.5) - (camera.height * (i + 0.5) / height);

  ray.origin = camera.e;
  ray.direction = (u * camera.u + v * camera.v - camera.d * camera.w).normalized();
}
