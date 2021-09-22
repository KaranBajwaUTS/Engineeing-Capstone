//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// iterate.cpp
//
// Code generation for function 'iterate'
//

// Include files
#include "iterate.h"
#include "SolveLP_internal_types.h"
#include "SolveLP_rtwutil.h"
#include "addAineqConstr.h"
#include "addBoundToActiveSetMatrix_.h"
#include "checkStoppingAndUpdateFval.h"
#include "computeFval_ReuseHx.h"
#include "computeGrad_StoreHx.h"
#include "computeQ_.h"
#include "compute_deltax.h"
#include "factorQR.h"
#include "feasibleratiotest.h"
#include "removeConstr.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include "xnrm2.h"
#include "xrotg.h"
#include "xtrsv.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
void iterate(const double H[576], const double f[75], g_struct_T *solution,
             h_struct_T *memspace, c_struct_T *workingset,
             i_struct_T *qrmanager, j_struct_T *cholmanager,
             b_struct_T *objective, const char options_SolverName[7],
             double options_StepTolerance, double options_ObjectiveLimit,
             int runTimeOptions_MaxIterations)
{
  static const char b[7]{'f', 'm', 'i', 'n', 'c', 'o', 'n'};
  double c;
  double minLambda;
  double s;
  double temp_tmp;
  int TYPE;
  int activeSetChangeID;
  int globalActiveConstrIdx;
  int i;
  int iyend;
  int nVar;
  boolean_T subProblemChanged;
  boolean_T updateFval;
  subProblemChanged = true;
  updateFval = true;
  activeSetChangeID = 0;
  TYPE = objective->objtype;
  nVar = workingset->nVar;
  globalActiveConstrIdx = 0;
  Objective::computeGrad_StoreHx(objective, H, f, solution->xstar);
  solution->fstar = Objective::computeFval_ReuseHx(
      objective, memspace->workspace_double, f, solution->xstar);
  if (solution->iterations < runTimeOptions_MaxIterations) {
    solution->state = -5;
  } else {
    solution->state = 0;
  }
  std::memset(&solution->lambda[0], 0, 148U * sizeof(double));
  int exitg1;
  do {
    exitg1 = 0;
    if (solution->state == -5) {
      int QRk0;
      int idx;
      int n;
      boolean_T guard1{false};
      guard1 = false;
      if (subProblemChanged) {
        int k;
        switch (activeSetChangeID) {
        case 1: {
          int ia;
          idx = 75 * (workingset->nActiveConstr - 1);
          QRk0 = qrmanager->mrows;
          iyend = qrmanager->ncols + 1;
          if (QRk0 < iyend) {
            iyend = QRk0;
          }
          qrmanager->minRowCol = iyend;
          QRk0 = 148 * qrmanager->ncols;
          if (qrmanager->mrows != 0) {
            iyend = QRk0 + qrmanager->mrows;
            if (QRk0 + 1 <= iyend) {
              std::memset(&qrmanager->QR[QRk0], 0,
                          (iyend - QRk0) * sizeof(double));
            }
            i = 148 * (qrmanager->mrows - 1) + 1;
            for (iyend = 1; iyend <= i; iyend += 148) {
              c = 0.0;
              n = (iyend + qrmanager->mrows) - 1;
              for (ia = iyend; ia <= n; ia++) {
                c += qrmanager->Q[ia - 1] *
                     workingset->ATwset[(idx + ia) - iyend];
              }
              n = QRk0 + div_nde_s32_floor(iyend - 1, 148);
              qrmanager->QR[n] += c;
            }
          }
          qrmanager->ncols++;
          qrmanager->jpvt[qrmanager->ncols - 1] = qrmanager->ncols;
          for (idx = qrmanager->mrows - 2; idx + 2 > qrmanager->ncols; idx--) {
            iyend = 148 * (qrmanager->ncols - 1);
            i = (idx + iyend) + 1;
            temp_tmp = qrmanager->QR[i];
            internal::blas::xrotg(&qrmanager->QR[idx + iyend], &temp_tmp, &c,
                                  &s);
            qrmanager->QR[i] = temp_tmp;
            iyend = 148 * idx;
            n = qrmanager->mrows;
            if (qrmanager->mrows >= 1) {
              for (k = 0; k < n; k++) {
                ia = iyend + k;
                minLambda = qrmanager->Q[ia + 148];
                temp_tmp = qrmanager->Q[ia];
                qrmanager->Q[ia + 148] = c * minLambda - s * temp_tmp;
                qrmanager->Q[ia] = c * temp_tmp + s * minLambda;
              }
            }
          }
        } break;
        case -1: {
          idx = globalActiveConstrIdx;
          if (qrmanager->usedPivoting) {
            idx = 1;
            while ((idx <= qrmanager->ncols) &&
                   (qrmanager->jpvt[idx - 1] != globalActiveConstrIdx)) {
              idx++;
            }
          }
          if (idx >= qrmanager->ncols) {
            qrmanager->ncols--;
          } else {
            qrmanager->jpvt[idx - 1] = qrmanager->jpvt[qrmanager->ncols - 1];
            i = qrmanager->minRowCol;
            for (k = 0; k < i; k++) {
              qrmanager->QR[k + 148 * (idx - 1)] =
                  qrmanager->QR[k + 148 * (qrmanager->ncols - 1)];
            }
            qrmanager->ncols--;
            QRk0 = qrmanager->mrows;
            iyend = qrmanager->ncols;
            if (QRk0 < iyend) {
              iyend = QRk0;
            }
            qrmanager->minRowCol = iyend;
            if (idx < qrmanager->mrows) {
              int b_k;
              int endIdx;
              int ia;
              QRk0 = qrmanager->mrows - 1;
              endIdx = qrmanager->ncols;
              if (QRk0 < endIdx) {
                endIdx = QRk0;
              }
              k = endIdx;
              iyend = 148 * (idx - 1);
              while (k >= idx) {
                i = k + iyend;
                temp_tmp = qrmanager->QR[i];
                internal::blas::xrotg(&qrmanager->QR[(k + iyend) - 1],
                                      &temp_tmp, &c, &s);
                qrmanager->QR[i] = temp_tmp;
                i = 148 * (k - 1);
                qrmanager->QR[k + i] = 0.0;
                QRk0 = k + 148 * idx;
                n = qrmanager->ncols - idx;
                if (n >= 1) {
                  for (b_k = 0; b_k < n; b_k++) {
                    ia = QRk0 + b_k * 148;
                    minLambda = qrmanager->QR[ia];
                    temp_tmp = qrmanager->QR[ia - 1];
                    qrmanager->QR[ia] = c * minLambda - s * temp_tmp;
                    qrmanager->QR[ia - 1] = c * temp_tmp + s * minLambda;
                  }
                }
                n = qrmanager->mrows;
                if (qrmanager->mrows >= 1) {
                  for (b_k = 0; b_k < n; b_k++) {
                    ia = i + b_k;
                    minLambda = qrmanager->Q[ia + 148];
                    temp_tmp = qrmanager->Q[ia];
                    qrmanager->Q[ia + 148] = c * minLambda - s * temp_tmp;
                    qrmanager->Q[ia] = c * temp_tmp + s * minLambda;
                  }
                }
                k--;
              }
              i = idx + 1;
              for (k = i; k <= endIdx; k++) {
                iyend = 148 * (k - 1);
                n = k + iyend;
                temp_tmp = qrmanager->QR[n];
                internal::blas::xrotg(&qrmanager->QR[(k + iyend) - 1],
                                      &temp_tmp, &c, &s);
                qrmanager->QR[n] = temp_tmp;
                QRk0 = k * 149;
                n = qrmanager->ncols - k;
                if (n >= 1) {
                  for (b_k = 0; b_k < n; b_k++) {
                    ia = QRk0 + b_k * 148;
                    minLambda = qrmanager->QR[ia];
                    temp_tmp = qrmanager->QR[ia - 1];
                    qrmanager->QR[ia] = c * minLambda - s * temp_tmp;
                    qrmanager->QR[ia - 1] = c * temp_tmp + s * minLambda;
                  }
                }
                n = qrmanager->mrows;
                if (qrmanager->mrows >= 1) {
                  for (b_k = 0; b_k < n; b_k++) {
                    ia = iyend + b_k;
                    minLambda = qrmanager->Q[ia + 148];
                    temp_tmp = qrmanager->Q[ia];
                    qrmanager->Q[ia + 148] = c * minLambda - s * temp_tmp;
                    qrmanager->Q[ia] = c * temp_tmp + s * minLambda;
                  }
                }
              }
            }
          }
        } break;
        default:
          QRManager::factorQR(qrmanager, workingset->ATwset, nVar,
                              workingset->nActiveConstr);
          QRManager::computeQ_(qrmanager, qrmanager->mrows);
          break;
        }
        iyend = memcmp(&options_SolverName[0], &b[0], 7);
        compute_deltax(H, solution, memspace, qrmanager, cholmanager, objective,
                       iyend == 0);
        if (solution->state != -5) {
          exitg1 = 1;
        } else if ((internal::blas::xnrm2(nVar, solution->searchDir) <
                    options_StepTolerance) ||
                   (workingset->nActiveConstr >= nVar)) {
          guard1 = true;
        } else {
          feasibleratiotest(
              solution->xstar, solution->searchDir, memspace->workspace_double,
              workingset->nVar, workingset->Aineq, workingset->bineq,
              workingset->lb, workingset->ub, workingset->indexLB,
              workingset->indexUB, workingset->sizes, workingset->isActiveIdx,
              workingset->isActiveConstr, workingset->nWConstr, TYPE == 5,
              &minLambda, &updateFval, &i, &iyend);
          if (updateFval) {
            switch (i) {
            case 3:
              WorkingSet::addAineqConstr(workingset, iyend);
              break;
            case 4:
              WorkingSet::addBoundToActiveSetMatrix_(workingset, 4, iyend);
              break;
            default:
              WorkingSet::addBoundToActiveSetMatrix_(workingset, 5, iyend);
              break;
            }
            activeSetChangeID = 1;
          } else {
            if (objective->objtype == 5) {
              if (internal::blas::xnrm2(objective->nvar, solution->searchDir) >
                  100.0 * static_cast<double>(objective->nvar) *
                      1.4901161193847656E-8) {
                solution->state = 3;
              } else {
                solution->state = 4;
              }
            }
            subProblemChanged = false;
            if (workingset->nActiveConstr == 0) {
              solution->state = 1;
            }
          }
          if ((nVar >= 1) && (!(minLambda == 0.0))) {
            iyend = nVar - 1;
            for (k = 0; k <= iyend; k++) {
              solution->xstar[k] += minLambda * solution->searchDir[k];
            }
          }
          Objective::computeGrad_StoreHx(objective, H, f, solution->xstar);
          updateFval = true;
          stopping::checkStoppingAndUpdateFval(
              &activeSetChangeID, f, solution, memspace, objective, workingset,
              qrmanager, options_ObjectiveLimit, runTimeOptions_MaxIterations,
              updateFval);
        }
      } else {
        if (0 <= nVar - 1) {
          std::memset(&solution->searchDir[0], 0, nVar * sizeof(double));
        }
        guard1 = true;
      }
      if (guard1) {
        iyend = qrmanager->ncols;
        if (qrmanager->ncols > 0) {
          minLambda = 100.0 * static_cast<double>(qrmanager->mrows) *
                      2.2204460492503131E-16;
          if ((qrmanager->mrows > 0) && (qrmanager->ncols > 0)) {
            updateFval = true;
          } else {
            updateFval = false;
          }
          if (updateFval) {
            boolean_T b_guard1{false};
            idx = qrmanager->ncols;
            b_guard1 = false;
            if (qrmanager->mrows < qrmanager->ncols) {
              QRk0 = qrmanager->mrows + 148 * (qrmanager->ncols - 1);
              while ((idx > qrmanager->mrows) &&
                     (std::abs(qrmanager->QR[QRk0 - 1]) >= minLambda)) {
                idx--;
                QRk0 -= 148;
              }
              updateFval = (idx == qrmanager->mrows);
              if (updateFval) {
                b_guard1 = true;
              }
            } else {
              b_guard1 = true;
            }
            if (b_guard1) {
              QRk0 = idx + 148 * (idx - 1);
              while ((idx >= 1) &&
                     (std::abs(qrmanager->QR[QRk0 - 1]) >= minLambda)) {
                idx--;
                QRk0 -= 149;
              }
              updateFval = (idx == 0);
            }
          }
          if (!updateFval) {
            solution->state = -7;
          } else {
            internal::blas::xgemv(qrmanager->mrows, qrmanager->ncols,
                                  qrmanager->Q, objective->grad,
                                  memspace->workspace_double);
            internal::blas::xtrsv(qrmanager->ncols, qrmanager->QR,
                                  memspace->workspace_double);
            for (idx = 0; idx < iyend; idx++) {
              solution->lambda[idx] = -memspace->workspace_double[idx];
            }
          }
        }
        if ((solution->state != -7) || (workingset->nActiveConstr > nVar)) {
          iyend = 0;
          minLambda = 0.0;
          i = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
          n = workingset->nActiveConstr;
          for (idx = i; idx <= n; idx++) {
            temp_tmp = solution->lambda[idx - 1];
            if (temp_tmp < minLambda) {
              minLambda = temp_tmp;
              iyend = idx;
            }
          }
          if (iyend == 0) {
            solution->state = 1;
          } else {
            activeSetChangeID = -1;
            globalActiveConstrIdx = iyend;
            subProblemChanged = true;
            WorkingSet::removeConstr(workingset, iyend);
            solution->lambda[iyend - 1] = 0.0;
          }
        } else {
          iyend = workingset->nActiveConstr;
          activeSetChangeID = 0;
          globalActiveConstrIdx = workingset->nActiveConstr;
          subProblemChanged = true;
          WorkingSet::removeConstr(workingset, workingset->nActiveConstr);
          solution->lambda[iyend - 1] = 0.0;
        }
        updateFval = false;
        stopping::checkStoppingAndUpdateFval(
            &activeSetChangeID, f, solution, memspace, objective, workingset,
            qrmanager, options_ObjectiveLimit, runTimeOptions_MaxIterations,
            updateFval);
      }
    } else {
      if (!updateFval) {
        solution->fstar = Objective::computeFval_ReuseHx(
            objective, memspace->workspace_double, f, solution->xstar);
      }
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (iterate.cpp)
