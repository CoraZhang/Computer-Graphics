#include "rgb_to_hsv.h"
#include <cmath>
#include <algorithm>



void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  auto R = r/255.0;
  auto G = g/255.0;
  auto B = b/255.0;
  auto Cmax = std::max(std::max(r,g),b);
  auto Cmin = std::min(std::min(r,g),b);
  auto diff = Cmax - Cmin;
  if(diff == 0) {
    h = 0;
  } else if(Cmax == r) {
    h = 60 * (fmod((g-b)*1.0/diff,6.0));
  } else if(Cmax == g) {
    h = 60 * ((b-r)*1.0/diff + 2);
  } else if(Cmax == b) {
    h = 60 * ((r-g)*1.0/diff + 4);
  }
  s = 0;
  if(Cmax != 0) s = diff*1.0/Cmax;
  v = Cmax / 255.0;
  ////////////////////////////////////////////////////////////////////////////
}
