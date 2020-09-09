#include "hsv_to_rgb.h"
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  auto c = v*s;
  auto x = c*(1-fabs(fmod(h/60,2)-1));
  auto m = v-c;
  double R,G,B;
  R=G=B=0.0;
  if(h >= 300) {
    R=c;
    G=0;
    B=x;
  } else if(h >= 240) {
    R=x;
    G=0;
    B=c;
  } else if(h >= 180) {
    R=0;
    G=x;
    B=c;
  } else if(h >= 120) {
    R=0;
    G=c;
    B=x;
  } else if(h >= 60) {
    R=x;
    G=c;
    B=0;
  } else if(h >= 0) {
    R=c;
    G=x;
    B=0;
  }
  r = (R+m)*255;
  g = (G+m)*255;
  b = (B+m)*255;
  ////////////////////////////////////////////////////////////////////////////
}
