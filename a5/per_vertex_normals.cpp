#include "per_vertex_normals.h"
#include "triangle_area_normal.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:

  for (int i = 0; i < V.rows(); i++) {
    Eigen::RowVector3d normal(0, 0, 0);
    for (int j = 0; j < F.rows(); j++) {
      auto a = V.row(F(j, 0));
      auto b = V.row(F(j, 1));
      auto c = V.row(F(j, 2));

      normal += triangle_area_normal(a, b, c);
    }
    N.row(i) = normal.normalized();
  }
  ////////////////////////////////////////////////////////////////////////////
}
