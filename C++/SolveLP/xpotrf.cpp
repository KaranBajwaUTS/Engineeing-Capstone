//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// xpotrf.cpp
//
// Code generation for function 'xpotrf'
//

// Include files
#include "xpotrf.h"
#include "SolveLP_rtwutil.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace internal {
namespace lapack {
int xpotrf(int n, double A[21904])
{
  int info;
  int j;
  boolean_T exitg1;
  info = 0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j <= n - 1)) {
    double c;
    double ssq;
    int idxA1j;
    int idxAjj;
    int nmj;
    idxA1j = j * 148;
    idxAjj = idxA1j + j;
    ssq = 0.0;
    if (j >= 1) {
      for (nmj = 0; nmj < j; nmj++) {
        c = A[idxA1j + nmj];
        ssq += c * c;
      }
    }
    ssq = A[idxAjj] - ssq;
    if (ssq > 0.0) {
      ssq = std::sqrt(ssq);
      A[idxAjj] = ssq;
      if (j + 1 < n) {
        int i;
        int ia0;
        int idxAjjp1;
        nmj = (n - j) - 2;
        ia0 = idxA1j + 149;
        idxAjjp1 = idxAjj + 149;
        if ((j != 0) && (nmj + 1 != 0)) {
          i = (idxA1j + 148 * nmj) + 149;
          for (int iac{ia0}; iac <= i; iac += 148) {
            int i1;
            c = 0.0;
            i1 = (iac + j) - 1;
            for (int ia{iac}; ia <= i1; ia++) {
              c += A[ia - 1] * A[(idxA1j + ia) - iac];
            }
            i1 = (idxAjj + div_nde_s32_floor((iac - idxA1j) - 149, 148) * 148) +
                 148;
            A[i1] += -c;
          }
        }
        ssq = 1.0 / ssq;
        i = (idxAjj + 148 * nmj) + 149;
        for (nmj = idxAjjp1; nmj <= i; nmj += 148) {
          A[nmj - 1] *= ssq;
        }
      }
      j++;
    } else {
      A[idxAjj] = ssq;
      info = j + 1;
      exitg1 = true;
    }
  }
  return info;
}

} // namespace lapack
} // namespace internal
} // namespace coder

// End of code generation (xpotrf.cpp)
