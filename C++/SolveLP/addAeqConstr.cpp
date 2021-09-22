//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// addAeqConstr.cpp
//
// Code generation for function 'addAeqConstr'
//

// Include files
#include "addAeqConstr.h"
#include "SolveLP_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace WorkingSet {
void addAeqConstr(c_struct_T *obj, int idx_local)
{
  int totalEq;
  totalEq = obj->nWConstr[0] + obj->nWConstr[1];
  if ((obj->nActiveConstr == totalEq) && (idx_local > obj->nWConstr[1])) {
    int i;
    int iAeq0;
    int iAw0;
    obj->nWConstr[1]++;
    obj->isActiveConstr[(obj->isActiveIdx[1] + idx_local) - 2] = true;
    obj->nActiveConstr++;
    obj->Wid[obj->nActiveConstr - 1] = 2;
    obj->Wlocalidx[obj->nActiveConstr - 1] = idx_local;
    iAeq0 = 75 * (idx_local - 1);
    iAw0 = 75 * (obj->nActiveConstr - 1);
    i = obj->nVar;
    for (int idx{0}; idx < i; idx++) {
      obj->ATwset[iAw0 + idx] = obj->Aeq[iAeq0 + idx];
    }
    obj->bwset[obj->nActiveConstr - 1] = obj->beq;
  } else {
    int i;
    int iAeq0;
    int iAw0;
    int idx;
    obj->nActiveConstr++;
    obj->Wid[obj->nActiveConstr - 1] = obj->Wid[totalEq];
    obj->Wlocalidx[obj->nActiveConstr - 1] = obj->Wlocalidx[totalEq];
    i = obj->nVar;
    for (idx = 0; idx < i; idx++) {
      obj->ATwset[idx + 75 * (obj->nActiveConstr - 1)] =
          obj->ATwset[idx + 75 * totalEq];
    }
    obj->bwset[obj->nActiveConstr - 1] = obj->bwset[totalEq];
    obj->nWConstr[1]++;
    obj->isActiveConstr[(obj->isActiveIdx[1] + idx_local) - 2] = true;
    obj->Wid[totalEq] = 2;
    obj->Wlocalidx[totalEq] = idx_local;
    iAeq0 = 75 * (idx_local - 1);
    iAw0 = 75 * totalEq;
    i = obj->nVar;
    for (idx = 0; idx < i; idx++) {
      obj->ATwset[iAw0 + idx] = obj->Aeq[iAeq0 + idx];
    }
    obj->bwset[totalEq] = obj->beq;
  }
}

} // namespace WorkingSet
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (addAeqConstr.cpp)
