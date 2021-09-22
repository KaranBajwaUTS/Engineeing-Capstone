//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xgemm.h
//
// Code generation for function 'xgemm'
//

#ifndef XGEMM_H
#define XGEMM_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void xgemm(int m, int n, int k, const double A[576], int lda,
           const double B[21904], int ib0, double C[11100]);

void xgemm(int m, int n, int k, const double A[21904], int ia0,
           const double B[11100], double C[21904]);

} // namespace blas
} // namespace internal
} // namespace coder

#endif
// End of code generation (xgemm.h)
