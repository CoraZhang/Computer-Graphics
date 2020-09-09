#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0; i < height; i++) {
    for(int j = width-1,k=0; k < width; j--,k++) {
      for(int x = 0; x < num_channels; x++)
        reflected[(i*width+k)*num_channels+x] = input[(i*width+j)*num_channels+x];
    }
  }

}
