#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Triplet<double> > ijv;
  const int n = V.rows();
  
  Eigen::SparseMatrix<double> Q(n,n);
  
  r.resize(E.rows());
  for (int i = 0; i < E.rows(); i++) {
    r(i) = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();
  }

  for (int i = 0; i < m.size(); i++) {
    ijv.emplace_back(Eigen::Triplet<double>(i, i, m(i)));
  }

  M.resize(n, n);
  M.setFromTriplets(ijv.begin(), ijv.end());

  signed_incidence_matrix_sparse(n, E, A);
  
  ijv.clear();  
  for (int i = 0; i < b.rows(); i++) {
    ijv.emplace_back(Eigen::Triplet<double>(i, b(i), 1));
  }

  C.resize(b.size(), n);  
  C.setFromTriplets(ijv.begin(), ijv.end());
  
  Q = k * A.transpose() * A + 1.0 / (delta_t * delta_t) * M + 1e10 * C.transpose() * C;

  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
