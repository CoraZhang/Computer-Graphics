#include "catmull_clark.h"
#include <map>
#include <utility>
#include <functional>
#include <vector>
#include <algorithm>

void construct_faces(Eigen::MatrixXd &SV,
                     Eigen::MatrixXi &SF,
                     Eigen::RowVector3d a,
                     Eigen::RowVector3d b,
                     Eigen::RowVector3d c,
                     Eigen::RowVector3d d)
{
  Eigen::RowVector4i face_index(-1, -1, -1, -1);
  std::vector <Eigen::RowVector3d> l = {a, b, c, d};
  int counter = 0;
  for (auto vertex : l) {
    for (int k = 0; k < SV.rows(); k++) {
      if (vertex.isApprox(SV.row(k))) {
        face_index(counter) = k;
      }
    }
    if (face_index(counter) == -1) {
      SV.conservativeResize(SV.rows() + 1, Eigen::NoChange);
      SV.row(SV.rows() - 1) = vertex;
      face_index(counter) = SV.rows() - 1;
    }
    counter++;
  }
  SF.conservativeResize(SF.rows() + 1, Eigen::NoChange);
  SF.row(SF.rows() - 1) = face_index;
}

Eigen::RowVector3d edge_point(const Eigen::MatrixXd &V,
                              std::map<std::pair<int, int>, std::vector<int>> &edge2adj_faces,
                              std::map<int, Eigen::RowVector3d> &face_point,
                              int p1,
                              int p2)
{
  std::pair<int, int> k = std::make_pair(p1, p2);
  Eigen::RowVector3d edgepoint(0, 0, 0);
  for (auto x: edge2adj_faces[k]) {
    edgepoint += face_point[x];
  }
  edgepoint += V.row(p1);
  edgepoint += V.row(p2);
  return (edgepoint / 4.0);
}

Eigen::RowVector3d update_point(std::map<int, std::vector<int>> &point2adj_faces,
                                std::map<int, Eigen::RowVector3d> &face_point,
                                std::map<int, std::vector<int>> &point2neighbors,
                                const Eigen::MatrixXd &V,
                                int p)
{
  Eigen::RowVector3d old = V.row(p);
  Eigen::RowVector3d avg_face(0, 0, 0);
  for (auto x: point2adj_faces[p]) {
    avg_face += face_point[x];
  }
  avg_face /= (double)point2adj_faces[p].size();

  Eigen::RowVector3d avg_edge(0, 0, 0);
  for (auto neighbor_idx: point2neighbors[p]) {
    avg_edge += (V.row(p) + V.row(neighbor_idx))/2.0;
  }
  avg_edge /= (double)point2neighbors[p].size();

  double n = point2adj_faces[p].size();
  return (avg_face + 2.0 * avg_edge + (n - 3) * old) / n;
}

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (num_iters == 0) {
    return;
  }
  
  std::map<int, Eigen::RowVector3d> face_point;
  std::map<int, std::vector<int>> point2adj_faces;
  std::map<std::pair<int, int>, std::vector<int>> edge2adj_faces;
  std::map<int, std::vector<int>> point2neighbors;

  for (int i = 0; i < F.rows(); i++) {
    Eigen::RowVector3d accumulator(0, 0, 0);
    for (int j = 0; j < F.cols(); j++) {
      accumulator += V.row(F(i, j));
      point2adj_faces[F(i, j)].emplace_back(i);
      std::pair<int, int> k = std::make_pair(F(i, j), F(i, (j + 1) % F.cols()));
      if (std::find(edge2adj_faces[k].begin(), edge2adj_faces[k].end(), i) == edge2adj_faces[k].end()) {
        edge2adj_faces[k].emplace_back(i);
      }
      k = std::make_pair(F(i, (j + 1) % F.cols()), F(i, j));
      if (std::find(edge2adj_faces[k].begin(), edge2adj_faces[k].end(), i) == edge2adj_faces[k].end()) {
        edge2adj_faces[k].emplace_back(i);
      }

      int neighbor = F(i, (j + 1) % F.cols());
      if (std::find(point2neighbors[F(i, j)].begin(), point2neighbors[F(i, j)].end(), neighbor) == point2neighbors[F(i, j)].end()) {
        point2neighbors[F(i, j)].emplace_back(neighbor);
      }
      neighbor = F(i, (j - 1 + F.cols()) % F.cols());
      if (std::find(point2neighbors[F(i, j)].begin(), point2neighbors[F(i, j)].end(), neighbor) == point2neighbors[F(i, j)].end()) {
        point2neighbors[F(i, j)].emplace_back(neighbor);
      }
    }

    face_point[i] = accumulator / 4.0;
  }

  SV.resize(0, 3);
  SF.resize(0, 4);
  for (int i = 0; i < F.rows(); i++) {
    for (int j = 0; j < F.cols(); j++) {

      Eigen::RowVector3d a = update_point(point2adj_faces, face_point, point2neighbors, V, F(i, j));
      Eigen::RowVector3d b = edge_point(V, edge2adj_faces, face_point, F(i, j), F(i, (j+1) % F.cols()));
      Eigen::RowVector3d c = face_point[i];
      Eigen::RowVector3d d = edge_point(V, edge2adj_faces, face_point, F(i, j), F(i, ((j-1) + F.cols()) % F.cols()));

      construct_faces(SV, SF, a, b, c, d);
    }
  }

  catmull_clark(Eigen::MatrixXd(SV), Eigen::MatrixXi(SF), num_iters - 1, SV, SF);
  ////////////////////////////////////////////////////////////////////////////

}
