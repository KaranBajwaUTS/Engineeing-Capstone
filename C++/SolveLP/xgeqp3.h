//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xgeqp3.h
//
// Code generation for function 'xgeqp3'
//

#ifndef XGEQP3_H
#define XGEQP3_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace lapack {
void xgeqp3(double A[21904], int m, int n, int jpvt[148], double tau[148]);

}
} // namespace internal
} // namespace coder

#endif
// End of code generation (xgeqp3.h)
