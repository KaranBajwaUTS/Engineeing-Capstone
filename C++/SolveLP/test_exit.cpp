//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// test_exit.cpp
//
// Code generation for function 'test_exit'
//

// Include files
#include "test_exit.h"
#include "SolveLP_internal_types.h"
#include "computeComplError.h"
#include "computeGradLag.h"
#include "computeQ_.h"
#include "rt_nonfinite.h"
#include "sortLambdaQP.h"
#include "updateWorkingSetForNewQP.h"
#include "xgemv.h"
#include "xgeqp3.h"
#include <algorithm>
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
void test_exit(e_struct_T *Flags, h_struct_T *memspace,
               d_struct_T *MeritFunction, c_struct_T *WorkingSet,
               g_struct_T *b_TrialState, i_struct_T *b_QRManager,
               const double lb[24], const double ub[24])
{
  double optimRelativeFactor;
  double s;
  double smax;
  int idx_max;
  int ix;
  int mFixed;
  int mLB;
  int mLambda;
  int mUB;
  int minDim;
  int nVar;
  boolean_T dxTooSmall;
  boolean_T exitg1;
  boolean_T isFeasible;
  nVar = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0] + 1;
  mLB = WorkingSet->sizes[3];
  mUB = WorkingSet->sizes[4];
  mLambda =
      ((WorkingSet->sizes[0] + WorkingSet->sizes[3]) + WorkingSet->sizes[4]) +
      48;
  stopping::computeGradLag(
      b_TrialState->gradLag, WorkingSet->nVar, b_TrialState->grad,
      WorkingSet->Aineq, WorkingSet->Aeq, WorkingSet->indexFixed,
      WorkingSet->sizes[0], WorkingSet->indexLB, WorkingSet->sizes[3],
      WorkingSet->indexUB, WorkingSet->sizes[4], b_TrialState->lambdasqp);
  if (WorkingSet->nVar < 1) {
    idx_max = 0;
  } else {
    idx_max = 1;
    if (WorkingSet->nVar > 1) {
      smax = std::abs(b_TrialState->grad[0]);
      for (minDim = 2; minDim <= nVar; minDim++) {
        s = std::abs(b_TrialState->grad[minDim - 1]);
        if (s > smax) {
          idx_max = minDim;
          smax = s;
        }
      }
    }
  }
  optimRelativeFactor =
      std::fmax(1.0, std::abs(b_TrialState->grad[idx_max - 1]));
  if (std::isinf(optimRelativeFactor)) {
    optimRelativeFactor = 1.0;
  }
  smax = std::fmax(0.0, std::abs(b_TrialState->cEq));
  for (ix = 0; ix < 48; ix++) {
    smax = std::fmax(smax, b_TrialState->cIneq[ix]);
  }
  for (ix = 0; ix < mLB; ix++) {
    idx_max = WorkingSet->indexLB[ix] - 1;
    smax = std::fmax(smax, lb[idx_max] - b_TrialState->xstarsqp[idx_max]);
  }
  for (ix = 0; ix < mUB; ix++) {
    idx_max = WorkingSet->indexUB[ix] - 1;
    smax = std::fmax(smax, b_TrialState->xstarsqp[idx_max] - ub[idx_max]);
  }
  MeritFunction->nlpPrimalFeasError = smax;
  if (b_TrialState->sqpIterations == 0) {
    MeritFunction->feasRelativeFactor = std::fmax(1.0, smax);
  }
  isFeasible = (smax <= 1.0E-6 * MeritFunction->feasRelativeFactor);
  dxTooSmall = true;
  smax = 0.0;
  ix = 0;
  exitg1 = false;
  while ((!exitg1) && (ix <= WorkingSet->nVar - 1)) {
    dxTooSmall = ((!std::isinf(b_TrialState->gradLag[ix])) &&
                  (!std::isnan(b_TrialState->gradLag[ix])));
    if (!dxTooSmall) {
      exitg1 = true;
    } else {
      smax = std::fmax(smax, std::abs(b_TrialState->gradLag[ix]));
      ix++;
    }
  }
  Flags->gradOK = dxTooSmall;
  MeritFunction->nlpDualFeasError = smax;
  if (!dxTooSmall) {
    Flags->done = true;
    if (isFeasible) {
      b_TrialState->sqpExitFlag = 2;
    } else {
      b_TrialState->sqpExitFlag = -2;
    }
  } else {
    MeritFunction->nlpComplError = stopping::computeComplError(
        b_TrialState->xstarsqp, b_TrialState->cIneq, WorkingSet->indexLB,
        WorkingSet->sizes[3], lb, WorkingSet->indexUB, WorkingSet->sizes[4], ub,
        b_TrialState->lambdasqp, WorkingSet->sizes[0] + 2);
    MeritFunction->firstOrderOpt =
        std::fmax(smax, MeritFunction->nlpComplError);
    if (b_TrialState->sqpIterations > 1) {
      double d;
      double nlpComplErrorTmp;
      stopping::b_computeGradLag(
          memspace->workspace_double, WorkingSet->nVar, b_TrialState->grad,
          WorkingSet->Aineq, WorkingSet->Aeq, WorkingSet->indexFixed,
          WorkingSet->sizes[0], WorkingSet->indexLB, WorkingSet->sizes[3],
          WorkingSet->indexUB, WorkingSet->sizes[4],
          b_TrialState->lambdasqp_old);
      s = 0.0;
      ix = 0;
      while ((ix <= WorkingSet->nVar - 1) &&
             ((!std::isinf(memspace->workspace_double[ix])) &&
              (!std::isnan(memspace->workspace_double[ix])))) {
        s = std::fmax(s, std::abs(memspace->workspace_double[ix]));
        ix++;
      }
      nlpComplErrorTmp = stopping::computeComplError(
          b_TrialState->xstarsqp, b_TrialState->cIneq, WorkingSet->indexLB,
          WorkingSet->sizes[3], lb, WorkingSet->indexUB, WorkingSet->sizes[4],
          ub, b_TrialState->lambdasqp_old, WorkingSet->sizes[0] + 1);
      d = std::fmax(s, nlpComplErrorTmp);
      if (d < std::fmax(smax, MeritFunction->nlpComplError)) {
        MeritFunction->nlpDualFeasError = s;
        MeritFunction->nlpComplError = nlpComplErrorTmp;
        MeritFunction->firstOrderOpt = d;
        if (0 <= mLambda) {
          std::copy(&b_TrialState->lambdasqp_old[0],
                    &b_TrialState->lambdasqp_old[mLambda + 1],
                    &b_TrialState->lambdasqp[0]);
        }
      } else if (0 <= mLambda) {
        std::copy(&b_TrialState->lambdasqp[0],
                  &b_TrialState->lambdasqp[mLambda + 1],
                  &b_TrialState->lambdasqp_old[0]);
      }
    } else if (0 <= mLambda) {
      std::copy(&b_TrialState->lambdasqp[0],
                &b_TrialState->lambdasqp[mLambda + 1],
                &b_TrialState->lambdasqp_old[0]);
    }
    if (isFeasible &&
        (MeritFunction->nlpDualFeasError <= 1.0E-6 * optimRelativeFactor) &&
        (MeritFunction->nlpComplError <= 1.0E-6 * optimRelativeFactor)) {
      Flags->done = true;
      b_TrialState->sqpExitFlag = 1;
    } else {
      Flags->done = false;
      if (isFeasible && (b_TrialState->sqpFval < -1.0E+20)) {
        Flags->done = true;
        b_TrialState->sqpExitFlag = -3;
      } else {
        boolean_T guard1{false};
        guard1 = false;
        if (b_TrialState->sqpIterations > 0) {
          dxTooSmall = true;
          ix = 0;
          exitg1 = false;
          while ((!exitg1) && (ix <= nVar - 1)) {
            if (1.0E-6 * std::fmax(1.0, std::abs(b_TrialState->xstarsqp[ix])) <=
                std::abs(b_TrialState->delta_x[ix])) {
              dxTooSmall = false;
              exitg1 = true;
            } else {
              ix++;
            }
          }
          if (dxTooSmall) {
            if (!isFeasible) {
              if (Flags->stepType != 2) {
                Flags->stepType = 2;
                Flags->failedLineSearch = false;
                Flags->stepAccepted = false;
                guard1 = true;
              } else {
                Flags->done = true;
                b_TrialState->sqpExitFlag = -2;
              }
            } else {
              int nActiveConstr;
              nActiveConstr = WorkingSet->nActiveConstr;
              if (WorkingSet->nActiveConstr > 0) {
                int rankR;
                internal::updateWorkingSetForNewQP(
                    b_TrialState->xstarsqp, WorkingSet, b_TrialState->cIneq,
                    b_TrialState->cEq, WorkingSet->sizes[3], lb,
                    WorkingSet->sizes[4], ub, WorkingSet->sizes[0]);
                for (minDim = 0; minDim < nActiveConstr; minDim++) {
                  b_TrialState->lambda[minDim] = 0.0;
                  idx_max = 75 * minDim;
                  ix = 148 * minDim;
                  for (rankR = 0; rankR < nVar; rankR++) {
                    b_QRManager->QR[ix + rankR] =
                        WorkingSet->ATwset[idx_max + rankR];
                  }
                }
                b_QRManager->usedPivoting = true;
                b_QRManager->mrows = nVar;
                b_QRManager->ncols = nActiveConstr;
                if (nVar < nActiveConstr) {
                  minDim = nVar;
                } else {
                  minDim = nActiveConstr;
                }
                b_QRManager->minRowCol = minDim;
                ::coder::internal::lapack::xgeqp3(
                    b_QRManager->QR, nVar, nActiveConstr, b_QRManager->jpvt,
                    b_QRManager->tau);
                QRManager::computeQ_(b_QRManager, nVar);
                if (nVar > nActiveConstr) {
                  idx_max = nVar;
                } else {
                  idx_max = nActiveConstr;
                }
                smax = std::abs(b_QRManager->QR[0]) *
                       std::fmin(1.4901161193847656E-8,
                                 static_cast<double>(idx_max) *
                                     2.2204460492503131E-16);
                rankR = 0;
                idx_max = 0;
                while ((rankR < minDim) &&
                       (std::abs(b_QRManager->QR[idx_max]) > smax)) {
                  rankR++;
                  idx_max += 149;
                }
                ::coder::internal::blas::xgemv(nVar, nVar, b_QRManager->Q,
                                               b_TrialState->grad,
                                               memspace->workspace_double);
                if (rankR != 0) {
                  for (int j{rankR}; j >= 1; j--) {
                    idx_max = (j + (j - 1) * 148) - 1;
                    memspace->workspace_double[j - 1] /=
                        b_QRManager->QR[idx_max];
                    for (int i{0}; i <= j - 2; i++) {
                      ix = (j - i) - 2;
                      memspace->workspace_double[ix] -=
                          memspace->workspace_double[j - 1] *
                          b_QRManager->QR[(idx_max - i) - 1];
                    }
                  }
                }
                if (nActiveConstr < minDim) {
                  minDim = nActiveConstr;
                }
                for (ix = 0; ix < minDim; ix++) {
                  b_TrialState->lambda[b_QRManager->jpvt[ix] - 1] =
                      memspace->workspace_double[ix];
                }
                for (ix = mFixed; ix <= mFixed; ix++) {
                  b_TrialState->lambda[ix - 1] = -b_TrialState->lambda[ix - 1];
                }
                qpactiveset::parseoutput::sortLambdaQP(
                    b_TrialState->lambda, WorkingSet->nActiveConstr,
                    WorkingSet->sizes, WorkingSet->isActiveIdx, WorkingSet->Wid,
                    WorkingSet->Wlocalidx, memspace->workspace_double);
                stopping::b_computeGradLag(
                    memspace->workspace_double, nVar, b_TrialState->grad,
                    WorkingSet->Aineq, WorkingSet->Aeq, WorkingSet->indexFixed,
                    mFixed - 1, WorkingSet->indexLB, mLB, WorkingSet->indexUB,
                    mUB, b_TrialState->lambda);
                smax = 0.0;
                ix = 0;
                while ((ix <= nVar - 1) &&
                       ((!std::isinf(memspace->workspace_double[ix])) &&
                        (!std::isnan(memspace->workspace_double[ix])))) {
                  smax =
                      std::fmax(smax, std::abs(memspace->workspace_double[ix]));
                  ix++;
                }
                s = stopping::computeComplError(
                    b_TrialState->xstarsqp, b_TrialState->cIneq,
                    WorkingSet->indexLB, mLB, lb, WorkingSet->indexUB, mUB, ub,
                    b_TrialState->lambda, mFixed);
                if ((smax <= 1.0E-6 * optimRelativeFactor) &&
                    (s <= 1.0E-6 * optimRelativeFactor)) {
                  MeritFunction->nlpDualFeasError = smax;
                  MeritFunction->nlpComplError = s;
                  MeritFunction->firstOrderOpt = std::fmax(smax, s);
                  if (0 <= mLambda) {
                    std::copy(&b_TrialState->lambda[0],
                              &b_TrialState->lambda[mLambda + 1],
                              &b_TrialState->lambdasqp[0]);
                  }
                  Flags->done = true;
                  b_TrialState->sqpExitFlag = 1;
                } else {
                  Flags->done = true;
                  b_TrialState->sqpExitFlag = 2;
                }
              } else {
                Flags->done = true;
                b_TrialState->sqpExitFlag = 2;
              }
            }
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }
        if (guard1) {
          if (b_TrialState->sqpIterations >= 400) {
            Flags->done = true;
            b_TrialState->sqpExitFlag = 0;
          } else if (b_TrialState->FunctionEvaluations >= 2400) {
            Flags->done = true;
            b_TrialState->sqpExitFlag = 0;
          }
        }
      }
    }
  }
}

} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (test_exit.cpp)
