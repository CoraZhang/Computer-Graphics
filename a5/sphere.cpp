#include "sphere.h"
#include <cmath>
#include <iostream>


#define _USE_MATH_DEFINES

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////
  int num_vertices = (num_faces_u + 1) * (num_faces_v + 1);
  V.resize(num_vertices, 3);
  UV.resize(num_vertices, 2);
  NV.resize(num_vertices, 3);

  int row = 0;
  for (int i = 0; i < num_faces_v + 1; i++) {
    double v = (double)i / num_faces_v;
    double theta = v * 2.0 * M_PI;

    for (int j = 0; j < num_faces_u + 1; j++) {
      double u = (double)j / num_faces_u;
      double phi = u * M_PI;

      double x = sin(phi) * cos(theta);
      double y = sin(phi) * sin(theta);
      double z = -cos(phi);

      V.row(row) = Eigen::RowVector3d(y, z, x);
      UV.row(row) = Eigen::RowVector2d(v, u);
      NV.row(row++) = Eigen::RowVector3d(y, z, x);
    }
  }
  
  int num_faces = num_faces_u * num_faces_v;
  F.resize(num_faces, 4);
  UF.resize(num_faces, 4);
  NF.resize(num_faces, 4);
  row = 0;
  for (int i = 0; i < num_faces_v; i++) {
    for (int j = 0; j < num_faces_u; j++) {
      int v1 = i * (num_faces_u + 1) + j;
      int v2 = v1 + 1;
      int v3 = (i + 1) * (num_faces_u + 1) + j + 1;
      int v4 = v3 - 1;

      F.row(row) = Eigen::RowVector4i(v1, v2, v3, v4);
      UF.row(row) = Eigen::RowVector4i(v1, v2, v3, v4);
      NF.row(row++) = Eigen::RowVector4i(v1, v2, v3, v4);
    }
  }


}
