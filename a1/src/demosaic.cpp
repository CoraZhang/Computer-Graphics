#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0; i < rgb.size(); i++) rgb[i] = 0;
  for(int i = 0, k = 0; i < height; i++) {
    if(i % 2 == 0) {
      for(int j = 0; j < width; j++) {
        int offset = j%2 + 1;
        rgb[(i*width+j)*3+offset] = bayer[k++];
      }
    } else {
      for(int j = 0; j < width; j++) {
        int offset = j%2;
        rgb[(i*width+j)*3+offset] = bayer[k++];
      }
    }
  }
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      for(int k = 0; k < 3; k++) { // rgb
        int cnt = 0;
        int sum = 0;
        for (int x = -1; x <= 1; x++) {
          for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) continue;
            int u = j+x;
            int v = i+y;
            if(u >= 0 && u < width && v >= 0 && v < height) {
              if(rgb[(v*width+u)*3+k]) {
                cnt++;
                sum+=rgb[(v*width+u)*3+k];
              }
            }
          }
        }
        rgb[(i*width+j)*3+k] = sum / cnt;
      }
    }
  }
}
