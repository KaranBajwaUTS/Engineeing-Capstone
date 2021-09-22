//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xtrsv.cpp
//
// Code generation for function 'xtrsv'
//

// Include files
#include "xtrsv.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace internal {
namespace blas {
void xtrsv(int n, const double A[21904], double x[11100])
{
  if (n != 0) {
    for (int j{n}; j >= 1; j--) {
      int jjA;
      jjA = (j + (j - 1) * 148) - 1;
      x[j - 1] /= A[jjA];
      for (int i{0}; i <= j - 2; i++) {
        int ix;
        ix = (j - i) - 2;
        x[ix] -= x[j - 1] * A[(jjA - i) - 1];
      }
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

// End of code generation (xtrsv.cpp)
