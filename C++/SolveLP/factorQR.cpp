//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// factorQR.cpp
//
// Code generation for function 'factorQR'
//

// Include files
#include "factorQR.h"
#include "SolveLP_internal_types.h"
#include "rt_nonfinite.h"
#include "xzgeqp3.h"
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace QRManager {
void factorQR(i_struct_T *obj, const double A[11100], int mrows, int ncols)
{
  int idx;
  int ix0;
  boolean_T guard1{false};
  ix0 = mrows * ncols;
  guard1 = false;
  if (ix0 > 0) {
    for (idx = 0; idx < ncols; idx++) {
      int iy0;
      ix0 = 75 * idx;
      iy0 = 148 * idx;
      for (int k{0}; k < mrows; k++) {
        obj->QR[iy0 + k] = A[ix0 + k];
      }
    }
    guard1 = true;
  } else if (ix0 == 0) {
    obj->mrows = mrows;
    obj->ncols = ncols;
    obj->minRowCol = 0;
  } else {
    guard1 = true;
  }
  if (guard1) {
    obj->usedPivoting = false;
    obj->mrows = mrows;
    obj->ncols = ncols;
    for (idx = 0; idx < ncols; idx++) {
      obj->jpvt[idx] = idx + 1;
    }
    if (mrows < ncols) {
      ix0 = mrows;
    } else {
      ix0 = ncols;
    }
    obj->minRowCol = ix0;
    std::memset(&obj->tau[0], 0, 148U * sizeof(double));
    if (ix0 >= 1) {
      std::memset(&obj->tau[0], 0, 148U * sizeof(double));
      internal::reflapack::qrf(obj->QR, mrows, ncols, ix0, obj->tau);
    }
  }
}

} // namespace QRManager
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (factorQR.cpp)
