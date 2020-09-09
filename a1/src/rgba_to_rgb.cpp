#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0,j = 0; i < rgba.size(); i+=4) {
    rgb[j++] = rgba[i+3]/255.0*rgba[i];
    rgb[j++] = rgba[i+3]/255.0*rgba[i+1];
    rgb[j++] = rgba[i+3]/255.0*rgba[i+2];
  }
}
