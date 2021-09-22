//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// partialColLDL3_.cpp
//
// Code generation for function 'partialColLDL3_'
//

// Include files
#include "partialColLDL3_.h"
#include "SolveLP_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace DynamicRegCholManager {
void partialColLDL3_(j_struct_T *obj, int LD_offset, int NColsRemain)
{
  int LD_diagOffset;
  int i;
  int i1;
  int i2;
  int ia;
  int idx;
  int ix;
  int k;
  int subRows;
  i = NColsRemain - 1;
  for (k = 0; k < 48; k++) {
    double y;
    subRows = (NColsRemain - k) - 1;
    LD_diagOffset = (LD_offset + 149 * k) - 1;
    for (idx = 0; idx <= subRows; idx++) {
      obj->workspace_ = obj->FMat[LD_diagOffset + idx];
    }
    for (idx = 0; idx <= i; idx++) {
      obj->workspace2_ = obj->workspace_;
    }
    y = obj->workspace2_;
    if ((NColsRemain != 0) && (k != 0)) {
      ix = LD_offset + k;
      i1 = 148 * (k - 1) + 1;
      for (idx = 1; idx <= i1; idx += 148) {
        i2 = (idx + NColsRemain) - 1;
        for (ia = idx; ia <= i2; ia++) {
          y += obj->workspace_ * -obj->FMat[ix - 1];
        }
        ix += 148;
      }
    }
    obj->workspace2_ = y;
    for (idx = 0; idx <= i; idx++) {
      obj->workspace_ = y;
    }
    for (idx = 0; idx <= subRows; idx++) {
      obj->FMat[LD_diagOffset + idx] = obj->workspace_;
    }
    for (idx = 0; idx < subRows; idx++) {
      i1 = (LD_diagOffset + idx) + 1;
      obj->FMat[i1] /= obj->FMat[LD_diagOffset];
    }
  }
  for (int j{48}; j <= i; j += 48) {
    int i3;
    int iy0;
    int m;
    int subBlockSize;
    int u1_tmp;
    u1_tmp = NColsRemain - j;
    if (48 < u1_tmp) {
      subBlockSize = 48;
    } else {
      subBlockSize = u1_tmp;
    }
    i1 = j + subBlockSize;
    i2 = i1 - 1;
    for (k = j; k <= i2; k++) {
      m = i1 - k;
      iy0 = (LD_offset + 149 * k) - 1;
      for (idx = 0; idx < 48; idx++) {
        obj->workspace2_ = obj->FMat[((LD_offset + k) + idx * 148) - 1];
      }
      ix = k + 1;
      if (m != 0) {
        i3 = k + 6957;
        for (idx = ix; idx <= i3; idx += 148) {
          subRows = (idx + m) - 1;
          for (ia = idx; ia <= subRows; ia++) {
            LD_diagOffset = (iy0 + ia) - idx;
            obj->FMat[LD_diagOffset] += obj->workspace_ * -obj->workspace2_;
          }
        }
      }
    }
    if (i1 < NColsRemain) {
      m = u1_tmp - subBlockSize;
      iy0 = ((LD_offset + subBlockSize) + 149 * j) - 1;
      i1 = subBlockSize - 1;
      for (idx = 0; idx < 48; idx++) {
        ix = (LD_offset + j) + idx * 148;
        for (subRows = 0; subRows <= i1; subRows++) {
          obj->workspace2_ = obj->FMat[(ix + subRows) - 1];
        }
      }
      if ((m != 0) && (subBlockSize != 0)) {
        ix = iy0 + 148 * (subBlockSize - 1);
        subRows = 0;
        for (LD_diagOffset = iy0; LD_diagOffset <= ix; LD_diagOffset += 148) {
          subRows++;
          i1 = subRows + 6956;
          for (idx = subRows; idx <= i1; idx += 148) {
            i2 = LD_diagOffset + 1;
            i3 = LD_diagOffset + m;
            for (u1_tmp = i2; u1_tmp <= i3; u1_tmp++) {
              obj->FMat[u1_tmp - 1] += -obj->workspace2_ * obj->workspace_;
            }
          }
        }
      }
    }
  }
}

} // namespace DynamicRegCholManager
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (partialColLDL3_.cpp)
