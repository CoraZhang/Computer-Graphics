#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);
  Eigen::Vector3d point = ray.origin + t * ray.direction;

  Eigen::Vector3d ambient = objects[hit_id]->material->ka;
  Eigen::Vector3d diffuse = objects[hit_id]->material->kd;
  Eigen::Vector3d specular = objects[hit_id]->material->ks;

  rgb += (ambient.array() * 0.1).matrix();

  for (auto& light: lights) {
    Eigen::Vector3d l_dir;
    double max_t;
    light->direction(point, l_dir, max_t);

    Ray t_ray;
    int t_hit_id;
    double t_t;
    Eigen::Vector3d t_n;
    
    t_ray.origin = point;
    t_ray.direction = l_dir;

    if (first_hit(t_ray, 1e-6, objects, t_hit_id, t_t, t_n) && t_t < max_t) {
      continue;
    }

    rgb += (diffuse.array() * std::max(0.0, n.dot(l_dir)) * light->I.array()).matrix();
    
    double exp = objects[hit_id]->material->phong_exponent;
    Eigen::Vector3d eye = -ray.direction.normalized();
    Eigen::Vector3d h = (eye + l_dir).normalized();
    rgb += (specular.array() * std::pow(std::max(0.0, n.dot(h)), exp) * light->I.array()).matrix();
  }

  return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
