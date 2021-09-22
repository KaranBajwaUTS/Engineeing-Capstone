//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// setProblemType.cpp
//
// Code generation for function 'setProblemType'
//

// Include files
#include "setProblemType.h"
#include "SolveLP_internal_types.h"
#include "modifyOverheadPhaseOne_.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace WorkingSet {
void setProblemType(c_struct_T *obj, int PROBLEM_TYPE)
{
  switch (PROBLEM_TYPE) {
  case 3: {
    int i;
    obj->nVar = 24;
    obj->mConstr = obj->mConstrOrig;
    if (obj->nWConstr[4] > 0) {
      i = obj->sizesNormal[4];
      for (int colOffsetATw{0}; colOffsetATw < i; colOffsetATw++) {
        obj->isActiveConstr[(obj->isActiveIdxNormal[4] + colOffsetATw) - 1] =
            obj->isActiveConstr[(obj->isActiveIdx[4] + colOffsetATw) - 1];
      }
    }
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesNormal[i];
    }
    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxNormal[i];
    }
  } break;
  case 1: {
    int i;
    obj->nVar = 25;
    obj->mConstr = obj->mConstrOrig + 1;
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesPhaseOne[i];
    }
    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxPhaseOne[i];
    }
    modifyOverheadPhaseOne_(obj);
  } break;
  case 2: {
    int i;
    obj->nVar = 74;
    obj->mConstr = 147;
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesRegularized[i];
    }
    if (obj->probType != 4) {
      int colOffsetATw;
      int colOffsetAineq;
      int i1;
      int idx_col;
      i = obj->sizes[0];
      for (idx_col = 0; idx_col < i; idx_col++) {
        colOffsetATw = 75 * idx_col;
        std::memset(&obj->ATwset[colOffsetATw + 24], 0, 50U * sizeof(double));
      }
      colOffsetATw = 75 * (obj->isActiveIdx[1] - 1);
      for (idx_col = 0; idx_col < 48; idx_col++) {
        colOffsetAineq = 75 * idx_col - 1;
        i = idx_col + 24;
        if (25 <= i) {
          std::memset(&obj->Aineq[colOffsetAineq + 25], 0,
                      (((i + colOffsetAineq) - colOffsetAineq) + -24) *
                          sizeof(double));
        }
        obj->Aineq[(idx_col + colOffsetAineq) + 25] = -1.0;
        i = idx_col + 26;
        if (i <= 74) {
          std::memset(&obj->Aineq[i + colOffsetAineq], 0,
                      (((colOffsetAineq - i) - colOffsetAineq) + 75) *
                          sizeof(double));
        }
        obj->Aeq[idx_col + 24] = 0.0;
        obj->ATwset[(idx_col + colOffsetATw) + 24] = 0.0;
      }
      obj->Aeq[72] = -1.0;
      obj->ATwset[colOffsetATw + 72] = -1.0;
      obj->Aeq[73] = 1.0;
      obj->ATwset[colOffsetATw + 73] = 1.0;
      colOffsetAineq = 24;
      i = obj->sizesNormal[3] + 1;
      i1 = obj->sizesRegularized[3];
      for (colOffsetATw = i; colOffsetATw <= i1; colOffsetATw++) {
        colOffsetAineq++;
        obj->indexLB[colOffsetATw - 1] = colOffsetAineq;
      }
      if (obj->nWConstr[4] > 0) {
        i = obj->sizesRegularized[4];
        for (colOffsetATw = 0; colOffsetATw < i; colOffsetATw++) {
          obj->isActiveConstr[obj->isActiveIdxRegularized[4] + colOffsetATw] =
              obj->isActiveConstr[(obj->isActiveIdx[4] + colOffsetATw) - 1];
        }
      }
      i = obj->isActiveIdx[4];
      i1 = obj->isActiveIdxRegularized[4] - 1;
      if (i <= i1) {
        std::memset(&obj->isActiveConstr[i + -1], 0,
                    ((i1 - i) + 1) * sizeof(boolean_T));
      }
      std::memset(&obj->lb[24], 0, 50U * sizeof(double));
      colOffsetAineq = obj->isActiveIdx[2];
      i = obj->nActiveConstr;
      for (idx_col = colOffsetAineq; idx_col <= i; idx_col++) {
        colOffsetATw = 75 * (idx_col - 1) - 1;
        switch (obj->Wid[idx_col - 1]) {
        case 3:
          i1 = obj->Wlocalidx[idx_col - 1] + 23;
          if (25 <= i1) {
            std::memset(&obj->ATwset[colOffsetATw + 25], 0,
                        (((i1 + colOffsetATw) - colOffsetATw) + -24) *
                            sizeof(double));
          }
          obj->ATwset[(obj->Wlocalidx[idx_col - 1] + colOffsetATw) + 24] = -1.0;
          i1 = obj->Wlocalidx[idx_col - 1] + 25;
          if (i1 <= 74) {
            std::memset(&obj->ATwset[i1 + colOffsetATw], 0,
                        (((colOffsetATw - i1) - colOffsetATw) + 75) *
                            sizeof(double));
          }
          break;
        default:
          std::memset(&obj->ATwset[colOffsetATw + 25], 0, 50U * sizeof(double));
          break;
        }
      }
    }
    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxRegularized[i];
    }
  } break;
  default: {
    int i;
    obj->nVar = 75;
    obj->mConstr = 148;
    for (i = 0; i < 5; i++) {
      obj->sizes[i] = obj->sizesRegPhaseOne[i];
    }
    for (i = 0; i < 6; i++) {
      obj->isActiveIdx[i] = obj->isActiveIdxRegPhaseOne[i];
    }
    modifyOverheadPhaseOne_(obj);
  } break;
  }
  obj->probType = PROBLEM_TYPE;
}

} // namespace WorkingSet
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (setProblemType.cpp)
