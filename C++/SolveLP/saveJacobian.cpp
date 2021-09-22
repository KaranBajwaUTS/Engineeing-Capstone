//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// saveJacobian.cpp
//
// Code generation for function 'saveJacobian'
//

// Include files
#include "saveJacobian.h"
#include "SolveLP_internal_types.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
namespace TrialState {
void saveJacobian(g_struct_T *obj, int nVar, const double JacCineqTrans[3600],
                  const double JacCeqTrans[75])
{
  int iCol;
  int iCol_old;
  iCol = -1;
  iCol_old = -1;
  for (int idx_col{0}; idx_col < 48; idx_col++) {
    for (int k{0}; k < nVar; k++) {
      obj->JacCineqTrans_old[(iCol_old + k) + 1] =
          JacCineqTrans[(iCol + k) + 1];
    }
    iCol += 75;
    iCol_old += 75;
  }
  if (0 <= nVar - 1) {
    std::copy(&JacCeqTrans[0], &JacCeqTrans[nVar], &obj->JacCeqTrans_old[0]);
  }
}

} // namespace TrialState
} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (saveJacobian.cpp)
