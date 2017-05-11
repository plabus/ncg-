/**
    NCG++
    clifford_algebra.cpp

    Purpose:
    Given the model parameters (p, q) initialise
    the entire ODD gamma matrices

    \Gamma_\mu = { \gamma_mu, \gamma_{\mu \nu \rho}, ... }

    and provide a print / read function.


    @author Peter Labus
    @version 0.1
    11.05.2017
*/

#include <iostream>
#include <vector>
#include "model_parameters.hpp"
#include "gamma_matrix.hpp"
#include "clifford_algebra.hpp"



// Member Functions:
// =================

CliffordAlgebra::CliffordAlgebra(ModelParameters const pqn)
  :
    pqn_(pqn),
    Gammas_(generate_small_gammas(pqn_))
{
}



// Non-Member Functions:
// =====================

std::ostream& operator<<(std::ostream& os, CliffordAlgebra const& A)
{
  for(auto i= 0; i < A.Gammas_.size(); ++i)
  {
    os << " Gamma " << i+1 << ":" << std::endl;
    os << A.Gammas_[i] << std::endl;
  }
  return os;
}


std::vector<GammaMatrix> generate_small_gammas(ModelParameters const pqn)
{
  /**
   *  \brief Generate all small gamma matrices.
   *
   *  Generate all small gamma matrices with signiture (d,0)
   *  and then multiply the last q matrices with I to
   *  get small gamma matrices of signature (p,q)
   */

  auto gammas = generate_euclidean_gammas(pqn.d(), pqn);

  const std::complex<int> I({0,1});
  for(auto i = pqn.p(); i != gammas.size(); ++i)
  {
    gammas[i] *= I;
  }

  return gammas;
}


// FIXME: This doesn't seem to work properly for d > 6
std::vector<GammaMatrix> generate_euclidean_gammas(
    const int d,                // dimensionality of Clifford algebra = # of gamma's
    const ModelParameters pqn   // provides gamma5_prefactor for odd dimensions,
                                // set to zero by default
)
{
  /**
   *  \brief Generate all small Euclidean gamma matrices in d dimensions.
   *
   *  Generate all small gamma matrices with
   *  signiture (d,0) recursively.
   */

  const PauliMatrices Pauli;
  std::vector<GammaMatrix> gammas;

  if( d == 1 )                         // Start of recursion
  {
    gammas.push_back( Unity(1) );
  }
  else if( d == 2 )                    // Start of recursion
  {
    gammas.push_back( Pauli.sigma1 );
    gammas.push_back( Pauli.sigma2 );
  }
  else if( d > 2 && d % 2 == 0 )       // Even-dim case
  {
    /** Gamma matrices in d even dimensions:
     *
     *  { gamma_mu (x) sigma1, 1I (x) sigma2, 1I (x) sigma3 },
     *
     *  where gamma_mu are the matrices d-2
     */
    auto small_gammas = generate_euclidean_gammas(d-2);
    auto one = Unity(d-2);

    // The following are outer (tensor) products
    for(auto gamma : small_gammas)
    {
      gammas.push_back( gamma % Pauli.sigma1 );
    }
    gammas.push_back( one % Pauli.sigma2 );
    gammas.push_back( one % Pauli.sigma3 );
  }
  else                                 // Odd-dim case
  {
    /** Gamma matrices in d odd dimensions:
     *
     *  { gamma_mu, gamma_5 },
     *
     *  where gamma_mu are the matrices d-1
     */
    gammas = generate_euclidean_gammas(d-1);
    auto prefactor = pqn.gamma5_prefactor();
    auto gamma_5 = prefactor * gammas.front();

    for(auto i = 1; i != gammas.size(); ++i)
    {
      gamma_5 *= gammas[i];
    }
    gammas.push_back( gamma_5 );
  }

  return gammas;
}