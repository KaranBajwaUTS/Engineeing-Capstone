//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// driver1.cpp
//
// Code generation for function 'driver1'
//

// Include files
#include "driver1.h"
#include "PresolveWorkingSet.h"
#include "SolveLP_internal_types.h"
#include "computeFval.h"
#include "iterate.h"
#include "maxConstraintViolation.h"
#include "phaseone.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
void driver(const double H[576], const double f[75], g_struct_T *solution,
            h_struct_T *memspace, c_struct_T *workingset, i_struct_T *qrmanager,
            j_struct_T *cholmanager, b_struct_T *objective, k_struct_T *options,
            k_struct_T *runTimeOptions)
{
  int nVar;
  boolean_T guard1{false};
  solution->iterations = 0;
  runTimeOptions->RemainFeasible = true;
  nVar = workingset->nVar - 1;
  guard1 = false;
  if (workingset->probType == 3) {
    int i;
    int idx;
    i = workingset->sizes[0];
    for (idx = 0; idx < i; idx++) {
      solution->xstar[workingset->indexFixed[idx] - 1] =
          workingset->ub[workingset->indexFixed[idx] - 1];
    }
    i = workingset->sizes[3];
    for (idx = 0; idx < i; idx++) {
      if (workingset->isActiveConstr[(workingset->isActiveIdx[3] + idx) - 1]) {
        solution->xstar[workingset->indexLB[idx] - 1] =
            -workingset->lb[workingset->indexLB[idx] - 1];
      }
    }
    i = workingset->sizes[4];
    for (idx = 0; idx < i; idx++) {
      if (workingset->isActiveConstr[(workingset->isActiveIdx[4] + idx) - 1]) {
        solution->xstar[workingset->indexUB[idx] - 1] =
            workingset->ub[workingset->indexUB[idx] - 1];
      }
    }
    initialize::PresolveWorkingSet(solution, memspace, workingset, qrmanager);
    if (solution->state >= 0) {
      guard1 = true;
    }
  } else {
    solution->state = 82;
    guard1 = true;
  }
  if (guard1) {
    solution->iterations = 0;
    solution->maxConstr =
        WorkingSet::b_maxConstraintViolation(workingset, solution->xstar);
    if (solution->maxConstr > 1.0E-6) {
      phaseone(H, f, solution, memspace, workingset, qrmanager, cholmanager,
               objective, options, runTimeOptions);
      if (solution->state != 0) {
        solution->maxConstr =
            WorkingSet::b_maxConstraintViolation(workingset, solution->xstar);
        if (solution->maxConstr > 1.0E-6) {
          std::memset(&solution->lambda[0], 0, 148U * sizeof(double));
          solution->fstar = Objective::computeFval(
              objective, memspace->workspace_double, H, f, solution->xstar);
          solution->state = -2;
        } else {
          if (solution->maxConstr > 0.0) {
            double maxConstr_new;
            if (0 <= nVar) {
              std::copy(&solution->xstar[0], &solution->xstar[nVar + 1],
                        &solution->searchDir[0]);
            }
            initialize::PresolveWorkingSet(solution, memspace, workingset,
                                           qrmanager);
            maxConstr_new = WorkingSet::b_maxConstraintViolation(
                workingset, solution->xstar);
            if (maxConstr_new >= solution->maxConstr) {
              solution->maxConstr = maxConstr_new;
              if (0 <= nVar) {
                std::copy(&solution->searchDir[0],
                          &solution->searchDir[nVar + 1], &solution->xstar[0]);
              }
            }
          }
          iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
                  objective, options->SolverName, options->StepTolerance,
                  options->ObjectiveLimit, runTimeOptions->MaxIterations);
        }
      }
    } else {
      iterate(H, f, solution, memspace, workingset, qrmanager, cholmanager,
              objective, options->SolverName, options->StepTolerance,
              options->ObjectiveLimit, runTimeOptions->MaxIterations);
    }
  }
}

} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (driver1.cpp)
