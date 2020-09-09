#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels == 1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::ofstream outfile(filename,std::ios::binary);
  if(!outfile || data.size() != width*height*num_channels) {
    return false;
  }
  if(num_channels == 3) {
    outfile << "P3" << std::endl;
  } else {
    outfile << "P2" << std::endl;
  }
  outfile << width << " " << height << std::endl;
  outfile << 255 << std::endl;
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      for (int k = 0; k < num_channels; k++) {
        outfile << (int) data[(i * width + j) * num_channels + k];
        if (k < num_channels - 1) outfile << " ";
      }
      outfile << "\n";
    }
  }
  outfile.close();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
