#include "over.h"
#include <iostream>

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      double alpha_a = A[(i*width+j)*4+3]/255.0;
      double alpha_b = B[(i*width+j)*4+3]/255.0;
      C[(i*width+j)*4+3] = alpha_a+alpha_b*(1-alpha_a);
      for(int k = 0 ; k < 3; k++) {
        C[(i*width+j)*4+k] = (alpha_a*A[(i*width+j)*4+k] + alpha_b*(1-alpha_a)*B[(i*width+j)*4+k])/C[(i*width+j)*4+3];
      }
      C[(i*width+j)*4+3] *= 255;
    }
  }
}
