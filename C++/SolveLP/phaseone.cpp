//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// phaseone.cpp
//
// Code generation for function 'phaseone'
//

// Include files
#include "phaseone.h"
#include "SolveLP_internal_types.h"
#include "computeFval.h"
#include "iterate.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
void phaseone(const double H[576], const double f[75], g_struct_T *solution,
              h_struct_T *memspace, c_struct_T *workingset,
              i_struct_T *qrmanager, j_struct_T *cholmanager,
              b_struct_T *objective, k_struct_T *options,
              const k_struct_T *runTimeOptions)
{
  int PHASEONE;
  int PROBTYPE_ORIG;
  int idxEndIneq;
  int idxStartIneq;
  int idx_global;
  int nVar_tmp_tmp;
  PROBTYPE_ORIG = workingset->probType;
  nVar_tmp_tmp = workingset->nVar;
  solution->xstar[workingset->nVar] = solution->maxConstr + 1.0;
  if (workingset->probType == 3) {
    PHASEONE = 1;
  } else {
    PHASEONE = 4;
  }
  idxStartIneq = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
  idxEndIneq = workingset->nActiveConstr;
  for (idx_global = idxStartIneq; idx_global <= idxEndIneq; idx_global++) {
    workingset->isActiveConstr
        [(workingset->isActiveIdx[workingset->Wid[idx_global - 1] - 1] +
          workingset->Wlocalidx[idx_global - 1]) -
         2] = false;
  }
  workingset->nWConstr[2] = 0;
  workingset->nWConstr[3] = 0;
  workingset->nWConstr[4] = 0;
  workingset->nActiveConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  WorkingSet::setProblemType(workingset, PHASEONE);
  objective->prev_objtype = objective->objtype;
  objective->prev_nvar = objective->nvar;
  objective->prev_hasLinear = objective->hasLinear;
  objective->objtype = 5;
  objective->nvar = nVar_tmp_tmp + 1;
  objective->gammaScalar = 1.0;
  objective->hasLinear = true;
  options->ObjectiveLimit = 1.0E-6;
  options->StepTolerance = 1.4901161193847657E-10;
  solution->fstar = Objective::computeFval(
      objective, memspace->workspace_double, H, f, solution->xstar);
  solution->state = 5;
  iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
          objective, options->SolverName, options->StepTolerance,
          options->ObjectiveLimit, runTimeOptions->MaxIterations);
  if (workingset
          ->isActiveConstr[(workingset->isActiveIdx[3] + workingset->sizes[3]) -
                           2]) {
    boolean_T exitg1;
    idx_global = workingset->sizes[0] + 1;
    exitg1 = false;
    while ((!exitg1) && (idx_global + 1 <= workingset->nActiveConstr)) {
      if ((workingset->Wid[idx_global] == 4) &&
          (workingset->Wlocalidx[idx_global] == workingset->sizes[3])) {
        idxStartIneq = workingset->Wid[idx_global] - 1;
        workingset->isActiveConstr
            [(workingset->isActiveIdx[workingset->Wid[idx_global] - 1] +
              workingset->Wlocalidx[idx_global]) -
             2] = false;
        workingset->Wid[idx_global] =
            workingset->Wid[workingset->nActiveConstr - 1];
        workingset->Wlocalidx[idx_global] =
            workingset->Wlocalidx[workingset->nActiveConstr - 1];
        idxEndIneq = workingset->nVar;
        for (PHASEONE = 0; PHASEONE < idxEndIneq; PHASEONE++) {
          workingset->ATwset[PHASEONE + 75 * idx_global] =
              workingset
                  ->ATwset[PHASEONE + 75 * (workingset->nActiveConstr - 1)];
        }
        workingset->bwset[idx_global] =
            workingset->bwset[workingset->nActiveConstr - 1];
        workingset->nActiveConstr--;
        workingset->nWConstr[idxStartIneq]--;
        exitg1 = true;
      } else {
        idx_global++;
      }
    }
  }
  PHASEONE = workingset->nActiveConstr - 1;
  while ((PHASEONE + 1 > workingset->sizes[0] + 1) &&
         (PHASEONE + 1 > nVar_tmp_tmp)) {
    idxStartIneq = workingset->Wid[PHASEONE] - 1;
    workingset->isActiveConstr
        [(workingset->isActiveIdx[workingset->Wid[PHASEONE] - 1] +
          workingset->Wlocalidx[PHASEONE]) -
         2] = false;
    workingset->Wid[PHASEONE] = workingset->Wid[workingset->nActiveConstr - 1];
    workingset->Wlocalidx[PHASEONE] =
        workingset->Wlocalidx[workingset->nActiveConstr - 1];
    idxEndIneq = workingset->nVar;
    for (idx_global = 0; idx_global < idxEndIneq; idx_global++) {
      workingset->ATwset[idx_global + 75 * PHASEONE] =
          workingset->ATwset[idx_global + 75 * (workingset->nActiveConstr - 1)];
    }
    workingset->bwset[PHASEONE] =
        workingset->bwset[workingset->nActiveConstr - 1];
    workingset->nActiveConstr--;
    workingset->nWConstr[idxStartIneq]--;
    PHASEONE--;
  }
  solution->maxConstr = solution->xstar[nVar_tmp_tmp];
  WorkingSet::setProblemType(workingset, PROBTYPE_ORIG);
  objective->objtype = objective->prev_objtype;
  objective->nvar = objective->prev_nvar;
  objective->hasLinear = objective->prev_hasLinear;
  options->ObjectiveLimit = rtMinusInf;
  options->StepTolerance = 1.0E-6;
}

} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (phaseone.cpp)
