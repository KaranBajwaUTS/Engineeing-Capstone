//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// updateWorkingSetForNewQP.cpp
//
// Code generation for function 'updateWorkingSetForNewQP'
//

// Include files
#include "updateWorkingSetForNewQP.h"
#include "SolveLP_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
namespace internal {
void updateWorkingSetForNewQP(const double xk[24], c_struct_T *WorkingSet,
                              const double cIneq[48], double cEq, int mLB,
                              const double lb[24], int mUB, const double ub[24],
                              int mFixed)
{
  int i;
  int idx;
  int iw0;
  int nVar;
  nVar = WorkingSet->nVar - 1;
  iw0 = 75 * mFixed;
  WorkingSet->beq = -cEq;
  WorkingSet->bwset[mFixed] = -cEq;
  for (i = 0; i <= nVar; i++) {
    WorkingSet->ATwset[iw0 + i] = WorkingSet->Aeq[i];
  }
  for (idx = 0; idx < 48; idx++) {
    WorkingSet->bineq[idx] = -cIneq[idx];
  }
  for (idx = 0; idx < mLB; idx++) {
    WorkingSet->lb[WorkingSet->indexLB[idx] - 1] =
        -lb[WorkingSet->indexLB[idx] - 1] + xk[WorkingSet->indexLB[idx] - 1];
  }
  for (idx = 0; idx < mUB; idx++) {
    WorkingSet->ub[WorkingSet->indexUB[idx] - 1] =
        ub[WorkingSet->indexUB[idx] - 1] - xk[WorkingSet->indexUB[idx] - 1];
  }
  for (idx = 0; idx < mFixed; idx++) {
    WorkingSet->ub[WorkingSet->indexFixed[idx] - 1] =
        ub[WorkingSet->indexFixed[idx] - 1] -
        xk[WorkingSet->indexFixed[idx] - 1];
    WorkingSet->bwset[idx] = ub[WorkingSet->indexFixed[idx] - 1] -
                             xk[WorkingSet->indexFixed[idx] - 1];
  }
  if (WorkingSet->nActiveConstr > mFixed + 1) {
    iw0 = mFixed + 2;
    i = WorkingSet->nActiveConstr;
    for (idx = iw0; idx <= i; idx++) {
      switch (WorkingSet->Wid[idx - 1]) {
      case 4:
        WorkingSet->bwset[idx - 1] =
            WorkingSet
                ->lb[WorkingSet->indexLB[WorkingSet->Wlocalidx[idx - 1] - 1] -
                     1];
        break;
      case 5:
        WorkingSet->bwset[idx - 1] =
            WorkingSet
                ->ub[WorkingSet->indexUB[WorkingSet->Wlocalidx[idx - 1] - 1] -
                     1];
        break;
      default: {
        WorkingSet->bwset[idx - 1] =
            WorkingSet->bineq[WorkingSet->Wlocalidx[idx - 1] - 1];
        if (WorkingSet->Wlocalidx[idx - 1] >= 48) {
          int iy0;
          iy0 = 75 * (idx - 1);
          for (int k{0}; k <= nVar; k++) {
            WorkingSet->ATwset[iy0 + k] = WorkingSet->Aineq[k + 3525];
          }
        }
      } break;
      }
    }
  }
}

} // namespace internal
} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (updateWorkingSetForNewQP.cpp)
