//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// fullColLDL2_.cpp
//
// Code generation for function 'fullColLDL2_'
//

// Include files
#include "fullColLDL2_.h"
#include "SolveLP_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace DynamicRegCholManager {
void fullColLDL2_(j_struct_T *obj, int LD_offset, int NColsRemain)
{
  for (int k{0}; k < NColsRemain; k++) {
    double alpha1;
    double y;
    int LD_diagOffset;
    int i;
    int jA;
    int subMatrixDim;
    LD_diagOffset = (LD_offset + 149 * k) - 1;
    alpha1 = -1.0 / obj->FMat[LD_diagOffset];
    subMatrixDim = (NColsRemain - k) - 2;
    for (jA = 0; jA <= subMatrixDim; jA++) {
      obj->workspace_ = obj->FMat[(LD_diagOffset + jA) + 1];
    }
    y = obj->workspace_;
    if (!(alpha1 == 0.0)) {
      jA = LD_diagOffset;
      for (int j{0}; j <= subMatrixDim; j++) {
        if (y != 0.0) {
          double temp;
          int i1;
          temp = y * alpha1;
          i = jA + 150;
          i1 = subMatrixDim + jA;
          for (int ijA{i}; ijA <= i1 + 150; ijA++) {
            obj->FMat[ijA - 1] += obj->workspace_ * temp;
          }
        }
        jA += 148;
      }
    }
    for (jA = 0; jA <= subMatrixDim; jA++) {
      i = (LD_diagOffset + jA) + 1;
      obj->FMat[i] /= obj->FMat[LD_diagOffset];
    }
  }
}

} // namespace DynamicRegCholManager
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (fullColLDL2_.cpp)
