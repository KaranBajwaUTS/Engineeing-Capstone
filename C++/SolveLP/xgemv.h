//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xgemv.h
//
// Code generation for function 'xgemv'
//

#ifndef XGEMV_H
#define XGEMV_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void xgemv(int m, int n, const double A[21904], const double x[75],
           double y[11100]);

}
} // namespace internal
} // namespace coder

#endif
// End of code generation (xgemv.h)
