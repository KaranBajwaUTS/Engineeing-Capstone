//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xgemv.cpp
//
// Code generation for function 'xgemv'
//

// Include files
#include "xgemv.h"
#include "SolveLP_rtwutil.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace internal {
namespace blas {
void xgemv(int m, int n, const double A[21904], const double x[75],
           double y[11100])
{
  if (m != 0) {
    int i;
    if (0 <= n - 1) {
      std::memset(&y[0], 0, n * sizeof(double));
    }
    i = 148 * (n - 1) + 1;
    for (int iac{1}; iac <= i; iac += 148) {
      double c;
      int i1;
      c = 0.0;
      i1 = (iac + m) - 1;
      for (int ia{iac}; ia <= i1; ia++) {
        c += A[ia - 1] * x[ia - iac];
      }
      i1 = div_nde_s32_floor(iac - 1, 148);
      y[i1] += c;
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

// End of code generation (xgemv.cpp)
