#include "signed_incidence_matrix_sparse.h"
#include <vector>

void signed_incidence_matrix_sparse(
  const int n,
  const Eigen::MatrixXi & E,
  Eigen::SparseMatrix<double>  & A)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Triplet<double> > ijv;
  A.resize(E.rows(),n);
 	for (int i = 0; i < A.rows(); i++){
    ijv.emplace_back(i, E(i, 0), 1);
    ijv.emplace_back(i, E(i, 1), -1);
 	}
  A.setFromTriplets(ijv.begin(),ijv.end());
  //////////////////////////////////////////////////////////////////////////////
}
