#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::ofstream ofs(filename);

  if (!ofs.is_open()) {
    return false;
  }

  // V
  for (int i = 0; i < V.rows(); i++) {
    ofs << "v " << V.row(i) << "\n";
  }

  // UV
  for (int i = 0; i < UV.rows(); i++) {
    ofs << "vt " << UV.row(i) << "\n";
  }

  // NV
  for (int i = 0; i < NV.rows(); i++) {
    ofs << "vn " << NV.row(i) << "\n";
  }

  // F
  for (int i = 0; i < F.rows(); i++) {
    ofs << "f ";
    for (int j = 0; j < F.cols(); j++) {
      ofs << F(i, j) + 1 << "/" << UF(i, j) + 1 << "/" << NF(i, j) + 1 << " ";
    }
    ofs << "\n";
  }

  ofs.close();
  ////////////////////////////////////////////////////////////////////////////
  return false;
}
