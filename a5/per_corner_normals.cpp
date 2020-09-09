#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  for (int i = 0; i < F.rows(); i++) {
    Eigen::RowVector3d a = V.row(F(i, 0));
    Eigen::RowVector3d b = V.row(F(i, 1));
    Eigen::RowVector3d c = V.row(F(i, 2));

    Eigen::RowVector3d tmp_n1 = triangle_area_normal(a, b, c);
    for (int j = 0; j < F.cols(); j++) {
      Eigen::RowVector3d normal(0, 0, 0);
      for (int k : VF[F(i, j)]) {
        Eigen::RowVector3d d = V.row(F(k, 0));
        Eigen::RowVector3d e = V.row(F(k, 1));
        Eigen::RowVector3d f = V.row(F(k, 2));

        Eigen::RowVector3d tmp_n2 = triangle_area_normal(d, e, f);

        if (tmp_n1.normalized().dot(tmp_n2.normalized()) > cos(corner_threshold * M_PI / 180.0)) {
          normal += tmp_n2;
        }
      }

      N.row(i * 3 + j) = normal.normalized();
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
