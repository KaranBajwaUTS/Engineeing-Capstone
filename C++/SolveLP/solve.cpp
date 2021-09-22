//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// solve.cpp
//
// Code generation for function 'solve'
//

// Include files
#include "solve.h"
#include "SolveLP_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace CholManager {
void solve(const j_struct_T *obj, double rhs[75])
{
  int n_tmp;
  n_tmp = obj->ndims;
  if (obj->ndims != 0) {
    int i;
    int j;
    int jA;
    for (j = 0; j < n_tmp; j++) {
      double temp;
      jA = j * 148;
      temp = rhs[j];
      for (i = 0; i < j; i++) {
        temp -= obj->FMat[jA + i] * rhs[i];
      }
      rhs[j] = temp / obj->FMat[jA + j];
    }
    for (j = n_tmp; j >= 1; j--) {
      jA = (j + (j - 1) * 148) - 1;
      rhs[j - 1] /= obj->FMat[jA];
      for (i = 0; i <= j - 2; i++) {
        int ix;
        ix = (j - i) - 2;
        rhs[ix] -= rhs[j - 1] * obj->FMat[(jA - i) - 1];
      }
    }
  }
}

} // namespace CholManager
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (solve.cpp)
