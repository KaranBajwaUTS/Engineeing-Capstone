//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// PresolveWorkingSet.cpp
//
// Code generation for function 'PresolveWorkingSet'
//

// Include files
#include "PresolveWorkingSet.h"
#include "RemoveDependentIneq_.h"
#include "SolveLP_internal_types.h"
#include "computeQ_.h"
#include "countsort.h"
#include "feasibleX0ForWorkingSet.h"
#include "maxConstraintViolation.h"
#include "rt_nonfinite.h"
#include "xgeqp3.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace initialize {
void PresolveWorkingSet(g_struct_T *solution, h_struct_T *memspace,
                        c_struct_T *workingset, i_struct_T *qrmanager)
{
  double tol;
  int idxDiag;
  int ix;
  int ix0;
  int mTotalWorkingEq_tmp_tmp;
  int mWorkingFixed;
  int nDepInd;
  int nVar;
  solution->state = 82;
  nVar = workingset->nVar - 1;
  mWorkingFixed = workingset->nWConstr[0];
  mTotalWorkingEq_tmp_tmp = workingset->nWConstr[0] + workingset->nWConstr[1];
  nDepInd = 0;
  if (mTotalWorkingEq_tmp_tmp > 0) {
    int i;
    int idx_col;
    int k;
    int u0;
    for (ix = 0; ix < mTotalWorkingEq_tmp_tmp; ix++) {
      for (idx_col = 0; idx_col <= nVar; idx_col++) {
        qrmanager->QR[ix + 148 * idx_col] =
            workingset->ATwset[idx_col + 75 * ix];
      }
    }
    idxDiag = workingset->nVar;
    nDepInd = mTotalWorkingEq_tmp_tmp - workingset->nVar;
    if (0 > nDepInd) {
      nDepInd = 0;
    }
    if (0 <= idxDiag - 1) {
      std::memset(&qrmanager->jpvt[0], 0, idxDiag * sizeof(int));
    }
    i = mTotalWorkingEq_tmp_tmp * workingset->nVar;
    if (i == 0) {
      qrmanager->mrows = mTotalWorkingEq_tmp_tmp;
      qrmanager->ncols = workingset->nVar;
      qrmanager->minRowCol = 0;
    } else {
      qrmanager->usedPivoting = true;
      qrmanager->mrows = mTotalWorkingEq_tmp_tmp;
      qrmanager->ncols = workingset->nVar;
      idxDiag = workingset->nVar;
      if (mTotalWorkingEq_tmp_tmp < idxDiag) {
        idxDiag = mTotalWorkingEq_tmp_tmp;
      }
      qrmanager->minRowCol = idxDiag;
      internal::lapack::xgeqp3(qrmanager->QR, mTotalWorkingEq_tmp_tmp,
                               workingset->nVar, qrmanager->jpvt,
                               qrmanager->tau);
    }
    tol =
        100.0 * static_cast<double>(workingset->nVar) * 2.2204460492503131E-16;
    u0 = workingset->nVar;
    if (u0 >= mTotalWorkingEq_tmp_tmp) {
      u0 = mTotalWorkingEq_tmp_tmp;
    }
    idxDiag = u0 + 148 * (u0 - 1);
    while ((idxDiag > 0) && (std::abs(qrmanager->QR[idxDiag - 1]) < tol)) {
      idxDiag -= 149;
      nDepInd++;
    }
    if (nDepInd > 0) {
      boolean_T exitg1;
      QRManager::computeQ_(qrmanager, qrmanager->mrows);
      idx_col = 0;
      exitg1 = false;
      while ((!exitg1) && (idx_col <= nDepInd - 1)) {
        double qtb;
        ix = 148 * ((mTotalWorkingEq_tmp_tmp - idx_col) - 1);
        qtb = 0.0;
        for (k = 0; k < mTotalWorkingEq_tmp_tmp; k++) {
          qtb += qrmanager->Q[ix + k] * workingset->bwset[k];
        }
        if (std::abs(qtb) >= tol) {
          nDepInd = -1;
          exitg1 = true;
        } else {
          idx_col++;
        }
      }
    }
    if (nDepInd > 0) {
      for (idx_col = 0; idx_col < mTotalWorkingEq_tmp_tmp; idx_col++) {
        idxDiag = 148 * idx_col;
        ix0 = 75 * idx_col;
        for (k = 0; k <= nVar; k++) {
          qrmanager->QR[idxDiag + k] = workingset->ATwset[ix0 + k];
        }
      }
      for (idx_col = 0; idx_col < mWorkingFixed; idx_col++) {
        qrmanager->jpvt[idx_col] = 1;
      }
      ix0 = workingset->nWConstr[0] + 1;
      if (ix0 <= mTotalWorkingEq_tmp_tmp) {
        std::memset(&qrmanager->jpvt[ix0 + -1], 0,
                    ((mTotalWorkingEq_tmp_tmp - ix0) + 1) * sizeof(int));
      }
      if (i == 0) {
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = mTotalWorkingEq_tmp_tmp;
        qrmanager->minRowCol = 0;
      } else {
        qrmanager->usedPivoting = true;
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = mTotalWorkingEq_tmp_tmp;
        qrmanager->minRowCol = u0;
        internal::lapack::xgeqp3(qrmanager->QR, workingset->nVar,
                                 mTotalWorkingEq_tmp_tmp, qrmanager->jpvt,
                                 qrmanager->tau);
      }
      for (idx_col = 0; idx_col < nDepInd; idx_col++) {
        memspace->workspace_int[idx_col] =
            qrmanager->jpvt[(mTotalWorkingEq_tmp_tmp - nDepInd) + idx_col];
      }
      utils::countsort(memspace->workspace_int, nDepInd,
                       memspace->workspace_sort, 1, mTotalWorkingEq_tmp_tmp);
      for (idx_col = nDepInd; idx_col >= 1; idx_col--) {
        i = workingset->nWConstr[0] + workingset->nWConstr[1];
        if (i != 0) {
          ix0 = memspace->workspace_int[idx_col - 1];
          if (ix0 <= i) {
            if ((workingset->nActiveConstr == i) || (ix0 == i)) {
              workingset->mEqRemoved++;
              i = memspace->workspace_int[idx_col - 1] - 1;
              workingset->indexEqRemoved = workingset->Wlocalidx[i];
              idxDiag = workingset->Wid[i] - 1;
              workingset->isActiveConstr[(workingset->isActiveIdx[idxDiag] +
                                          workingset->Wlocalidx[i]) -
                                         2] = false;
              workingset->Wid[i] =
                  workingset->Wid[workingset->nActiveConstr - 1];
              workingset->Wlocalidx[i] =
                  workingset->Wlocalidx[workingset->nActiveConstr - 1];
              ix0 = workingset->nVar;
              for (u0 = 0; u0 < ix0; u0++) {
                workingset
                    ->ATwset[u0 +
                             75 * (memspace->workspace_int[idx_col - 1] - 1)] =
                    workingset
                        ->ATwset[u0 + 75 * (workingset->nActiveConstr - 1)];
              }
              workingset->bwset[i] =
                  workingset->bwset[workingset->nActiveConstr - 1];
              workingset->nActiveConstr--;
              workingset->nWConstr[idxDiag]--;
            } else {
              workingset->mEqRemoved++;
              ix = workingset->Wid[ix0 - 1] - 1;
              workingset->indexEqRemoved = workingset->Wlocalidx[ix0 - 1];
              workingset->isActiveConstr
                  [(workingset->isActiveIdx[workingset->Wid[ix0 - 1] - 1] +
                    workingset->Wlocalidx[ix0 - 1]) -
                   2] = false;
              workingset->Wid[ix0 - 1] = workingset->Wid[i - 1];
              workingset->Wlocalidx[ix0 - 1] = workingset->Wlocalidx[i - 1];
              idxDiag = workingset->nVar;
              for (u0 = 0; u0 < idxDiag; u0++) {
                workingset->ATwset[u0 + 75 * (ix0 - 1)] =
                    workingset->ATwset[u0 + 75 * (i - 1)];
              }
              workingset->bwset[ix0 - 1] = workingset->bwset[i - 1];
              workingset->Wid[i - 1] =
                  workingset->Wid[workingset->nActiveConstr - 1];
              workingset->Wlocalidx[i - 1] =
                  workingset->Wlocalidx[workingset->nActiveConstr - 1];
              ix0 = workingset->nVar;
              for (u0 = 0; u0 < ix0; u0++) {
                workingset->ATwset[u0 + 75 * (i - 1)] =
                    workingset
                        ->ATwset[u0 + 75 * (workingset->nActiveConstr - 1)];
              }
              workingset->bwset[i - 1] =
                  workingset->bwset[workingset->nActiveConstr - 1];
              workingset->nActiveConstr--;
              workingset->nWConstr[ix]--;
            }
          }
        }
      }
    }
  }
  if ((nDepInd != -1) && (workingset->nActiveConstr <= 148)) {
    boolean_T guard1{false};
    boolean_T okWorkingSet;
    RemoveDependentIneq_(workingset, qrmanager, memspace, 100.0);
    okWorkingSet = feasibleX0ForWorkingSet(
        memspace->workspace_double, solution->xstar, workingset, qrmanager);
    guard1 = false;
    if (!okWorkingSet) {
      RemoveDependentIneq_(workingset, qrmanager, memspace, 1000.0);
      okWorkingSet = feasibleX0ForWorkingSet(
          memspace->workspace_double, solution->xstar, workingset, qrmanager);
      if (!okWorkingSet) {
        solution->state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1 && (workingset->nWConstr[0] + workingset->nWConstr[1] ==
                   workingset->nVar)) {
      tol = WorkingSet::b_maxConstraintViolation(workingset, solution->xstar);
      if (tol > 1.0E-6) {
        solution->state = -2;
      }
    }
  } else {
    solution->state = -3;
    idxDiag = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
    ix = workingset->nActiveConstr;
    for (ix0 = idxDiag; ix0 <= ix; ix0++) {
      workingset->isActiveConstr
          [(workingset->isActiveIdx[workingset->Wid[ix0 - 1] - 1] +
            workingset->Wlocalidx[ix0 - 1]) -
           2] = false;
    }
    workingset->nWConstr[2] = 0;
    workingset->nWConstr[3] = 0;
    workingset->nWConstr[4] = 0;
    workingset->nActiveConstr =
        workingset->nWConstr[0] + workingset->nWConstr[1];
  }
}

} // namespace initialize
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (PresolveWorkingSet.cpp)
