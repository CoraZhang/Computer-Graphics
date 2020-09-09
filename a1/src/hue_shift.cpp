#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <cmath>

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      double r = rgb[(i*width+j)*3];
      double g = rgb[(i*width+j)*3+1];
      double b = rgb[(i*width+j)*3+2];
      double h,s,v;
      rgb_to_hsv(r,g,b,h,s,v);
      h = fmod(h+shift+360,360);
      hsv_to_rgb(h,s,v,r,g,b);
      shifted[(i*width+j)*3] = r;
      shifted[(i*width+j)*3+1] = g;
      shifted[(i*width+j)*3+2] = b;
    }
  }

}
