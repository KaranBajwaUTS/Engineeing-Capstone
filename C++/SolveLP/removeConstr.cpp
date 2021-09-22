//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// removeConstr.cpp
//
// Code generation for function 'removeConstr'
//

// Include files
#include "removeConstr.h"
#include "SolveLP_internal_types.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace WorkingSet {
void removeConstr(c_struct_T *obj, int idx_global)
{
  int TYPE_tmp;
  int i;
  TYPE_tmp = obj->Wid[idx_global - 1] - 1;
  obj->isActiveConstr[(obj->isActiveIdx[TYPE_tmp] +
                       obj->Wlocalidx[idx_global - 1]) -
                      2] = false;
  obj->Wid[idx_global - 1] = obj->Wid[obj->nActiveConstr - 1];
  obj->Wlocalidx[idx_global - 1] = obj->Wlocalidx[obj->nActiveConstr - 1];
  i = obj->nVar;
  for (int idx{0}; idx < i; idx++) {
    obj->ATwset[idx + 75 * (idx_global - 1)] =
        obj->ATwset[idx + 75 * (obj->nActiveConstr - 1)];
  }
  obj->bwset[idx_global - 1] = obj->bwset[obj->nActiveConstr - 1];
  obj->nActiveConstr--;
  obj->nWConstr[TYPE_tmp]--;
}

} // namespace WorkingSet
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (removeConstr.cpp)
