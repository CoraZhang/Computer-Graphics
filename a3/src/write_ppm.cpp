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
  if (width == 0 || height == 0) {
    return false;
  }

  std::ofstream ofs(filename, std::ios::binary | std::ios::out | std::ios::trunc);

  if (ofs.fail()) {
    std::perror("open");
    exit(EXIT_FAILURE);
  } else if (!ofs.is_open()) {
    return false;
  }

  if (num_channels == 1) {
    ofs << "P5\n";
  } else {
    ofs << "P6\n";
  }

  ofs << width << " " << height << "\n" << "255" << std::endl;

  int num_subpixels = width * height * num_channels;
  for (int i = 0; i < num_subpixels; i++) {
    ofs << data[i];
  }

  ofs.close();
  return true;
}
