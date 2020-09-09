#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  if (keyframes.empty()) {
    return Eigen::Vector3d(0,0,0);
  }

  Eigen::Vector3d res(0, 0, 0);

  double l = std::fmod(t, keyframes.back().first);
  
  double a_0, a_1, a_2, a_3;
  Eigen::Vector3d b_0, b_1, b_2, b_3, c_0, c_2;

  int idx = 0;
  for (int i = 0; i < keyframes.size() - 1; i++){
    if ((keyframes[i].first <= l) && (l < keyframes[i + 1].first))
      idx = i;
  }

  int ost = (idx == 0) ? 0 : 1;

  a_0 = keyframes[idx - ost].first;
  a_1 = keyframes[idx].first;
  a_2 = keyframes[idx + 1].first;
  a_3 = keyframes[idx + 2].first;

  b_0 = keyframes[idx - ost].second;
  b_1 = keyframes[idx].second;
  b_2 = keyframes[idx + 1].second;
  b_3 = keyframes[idx + 2].second;

  c_0 = (b_2 - b_0) / (a_2 - a_0);
  c_2 = (b_3 - b_1) / (a_3 - a_1);

  double e = (l - a_1) / (a_2 - a_1);

  res = (2 * pow(e, 3) - 3 * pow(e, 2) + 1) * b_1 + (pow(e, 3) - 2 * pow(e, 2) + e) * c_0 + \
        (-2 * pow(e, 3) + 3 * pow(e, 2)) * b_2 + (pow(e, 3) - pow(e, 2))  * c_2;

  return res;
  /////////////////////////////////////////////////////////////////////////////
}
