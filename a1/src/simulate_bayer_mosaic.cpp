#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0,k = 0; i < height; i++) {
    if(i % 2 == 0) {
      for(int j = 0; j < width; j++) {
        int offset = j%2 + 1;
        bayer[k++] = rgb[(i*width+j)*3+offset];
      }
    } else {
      for(int j = 0; j < width; j++) {
        int offset = j%2;
        bayer[k++] = rgb[(i*width+j)*3+offset];
      }
    }
  }
}
