/**
    NCG++
    clifford_algebra.hpp

    Purpose:
    Given the model parameters (p, q) initialise
    the entire ODD gamma matrices

    \Gamma_\mu = { \gamma_mu, \gamma_{\mu \nu \rho}, ... }

    and provide a print / read function.


    @author Peter Labus
    @version 0.1
    09.05.2017
*/

#pragma once

#include <iostream>
#include <vector>
#include "model_parameters.hpp"
#include "gamma_matrix.hpp"



class CliffordAlgebra
{
  public:

    CliffordAlgebra(void) = delete;
    explicit CliffordAlgebra(ModelParameters const pqn);

    friend std::ostream& operator<<(std::ostream&, CliffordAlgebra const& A);


  private:

    const ModelParameters pqn_;
    std::vector<GammaMatrix> Gammas_;
};



// Non-Member Functions:
// =====================

// Generates the Clifford Algebra with signature (p,q)
std::vector<GammaMatrix> generate_small_gammas(
    const ModelParameters pqn
);

// Generates the Euclidean Clifford Algebra with signature (d=p+q,0)
std::vector<GammaMatrix> generate_euclidean_gammas(
    const int d,                                        // dimensionality of Clifford algebra = # of gamma's
    const ModelParameters pqn = ModelParameters(0,0,0)  // provides gamma5_prefactor for odd dimensions,
                                                        // set to zero by default
);