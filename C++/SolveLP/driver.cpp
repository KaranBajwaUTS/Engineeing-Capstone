//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// driver.cpp
//
// Code generation for function 'driver'
//

// Include files
#include "driver.h"
#include "BFGSUpdate.h"
#include "SolveLP.h"
#include "SolveLP_internal_types.h"
#include "anonymous_function.h"
#include "computeConstraints_.h"
#include "computeDualFeasError.h"
#include "computeFiniteDifferences.h"
#include "computeGradLag.h"
#include "linesearch.h"
#include "rt_nonfinite.h"
#include "saveJacobian.h"
#include "step.h"
#include "test_exit.h"
#include "updateWorkingSetForNewQP.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
void driver(const double lb[24], const double ub[24], g_struct_T *b_TrialState,
            d_struct_T *MeritFunction, const l_struct_T *FcnEvaluator,
            m_struct_T *FiniteDifferences, h_struct_T *memspace,
            c_struct_T *WorkingSet, i_struct_T *b_QRManager,
            b_struct_T *QPObjective, double Hessian[576],
            j_struct_T *b_CholManager)
{
  static const signed char iv[576]{
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  static const char qpoptions_SolverName[7]{'f', 'm', 'i', 'n', 'c', 'o', 'n'};
  e_struct_T Flags;
  k_struct_T b_expl_temp;
  k_struct_T expl_temp;
  double s;
  double smax;
  int b_mLB;
  int b_mUB;
  int idxFiniteLB;
  int idx_max;
  int mConstr_tmp;
  int mFixed;
  int mLB;
  int mUB;
  int nVar_tmp;
  int qpoptions_MaxIterations;
  boolean_T isFeasible;
  std::memset(&b_CholManager->FMat[0], 0, 21904U * sizeof(double));
  b_CholManager->ldm = 148;
  b_CholManager->ndims = 0;
  b_CholManager->info = 0;
  b_CholManager->scaleFactor = 0.0;
  b_CholManager->ConvexCheck = true;
  b_CholManager->regTol_ = rtInf;
  b_CholManager->workspace_ = rtInf;
  b_CholManager->workspace2_ = rtInf;
  for (mLB = 0; mLB < 576; mLB++) {
    Hessian[mLB] = iv[mLB];
  }
  nVar_tmp = WorkingSet->nVar;
  mFixed = WorkingSet->sizes[0];
  b_mLB = WorkingSet->sizes[3];
  mUB = WorkingSet->sizes[4];
  mConstr_tmp =
      ((WorkingSet->sizes[0] + WorkingSet->sizes[3]) + WorkingSet->sizes[4]) +
      48;
  idx_max = WorkingSet->nVar;
  idxFiniteLB = ((WorkingSet->sizes[3] + WorkingSet->sizes[4]) +
                 (WorkingSet->sizes[0] << 1)) +
                48;
  if (idx_max > idxFiniteLB) {
    idxFiniteLB = idx_max;
  }
  qpoptions_MaxIterations = 10 * idxFiniteLB;
  b_TrialState->steplength = 1.0;
  Flags.fevalOK = true;
  Flags.stepAccepted = false;
  Flags.failedLineSearch = false;
  Flags.stepType = 1;
  mLB = WorkingSet->sizes[3];
  b_mUB = WorkingSet->sizes[4];
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
      for (idxFiniteLB = 2; idxFiniteLB <= nVar_tmp; idxFiniteLB++) {
        s = std::abs(b_TrialState->grad[idxFiniteLB - 1]);
        if (s > smax) {
          idx_max = idxFiniteLB;
          smax = s;
        }
      }
    }
  }
  smax = std::fmax(1.0, std::abs(b_TrialState->grad[idx_max - 1]));
  if (std::isinf(smax)) {
    smax = 1.0;
  }
  s = std::fmax(0.0, std::abs(b_TrialState->cEq));
  for (idx_max = 0; idx_max < 48; idx_max++) {
    s = std::fmax(s, b_TrialState->cIneq[idx_max]);
  }
  for (idx_max = 0; idx_max < mLB; idx_max++) {
    idxFiniteLB = WorkingSet->indexLB[idx_max] - 1;
    s = std::fmax(s, lb[idxFiniteLB] - b_TrialState->xstarsqp[idxFiniteLB]);
  }
  for (idx_max = 0; idx_max < b_mUB; idx_max++) {
    idxFiniteLB = WorkingSet->indexUB[idx_max] - 1;
    s = std::fmax(s, b_TrialState->xstarsqp[idxFiniteLB] - ub[idxFiniteLB]);
  }
  MeritFunction->nlpPrimalFeasError = s;
  MeritFunction->feasRelativeFactor = std::fmax(1.0, s);
  isFeasible = (s <= 1.0E-6 * MeritFunction->feasRelativeFactor);
  stopping::computeDualFeasError(WorkingSet->nVar, b_TrialState->gradLag,
                                 &Flags.gradOK,
                                 &MeritFunction->nlpDualFeasError);
  if (!Flags.gradOK) {
    Flags.done = true;
    if (isFeasible) {
      b_TrialState->sqpExitFlag = 2;
    } else {
      b_TrialState->sqpExitFlag = -2;
    }
  } else {
    MeritFunction->nlpComplError = 0.0;
    MeritFunction->firstOrderOpt =
        std::fmax(MeritFunction->nlpDualFeasError, 0.0);
    if (0 <= mConstr_tmp) {
      std::copy(&b_TrialState->lambdasqp[0],
                &b_TrialState->lambdasqp[mConstr_tmp + 1],
                &b_TrialState->lambdasqp_old[0]);
    }
    if (isFeasible && (MeritFunction->nlpDualFeasError <= 1.0E-6 * smax)) {
      Flags.done = true;
      b_TrialState->sqpExitFlag = 1;
    } else {
      Flags.done = false;
      if (isFeasible && (b_TrialState->sqpFval < -1.0E+20)) {
        Flags.done = true;
        b_TrialState->sqpExitFlag = -3;
      } else if (b_TrialState->FunctionEvaluations >= 2400) {
        Flags.done = true;
        b_TrialState->sqpExitFlag = 0;
      }
    }
  }
  TrialState::saveJacobian(b_TrialState, WorkingSet->nVar, WorkingSet->Aineq,
                           WorkingSet->Aeq);
  b_TrialState->sqpFval_old = b_TrialState->sqpFval;
  for (idxFiniteLB = 0; idxFiniteLB < 24; idxFiniteLB++) {
    b_TrialState->xstarsqp_old[idxFiniteLB] =
        b_TrialState->xstarsqp[idxFiniteLB];
    b_TrialState->grad_old[idxFiniteLB] = b_TrialState->grad[idxFiniteLB];
  }
  std::copy(&b_TrialState->cIneq[0], &b_TrialState->cIneq[48],
            &b_TrialState->cIneq_old[0]);
  b_TrialState->cEq_old = b_TrialState->cEq;
  if (!Flags.done) {
    b_TrialState->sqpIterations = 1;
  }
  while (!Flags.done) {
    while (!(Flags.stepAccepted || Flags.failedLineSearch)) {
      internal::updateWorkingSetForNewQP(b_TrialState->xstarsqp, WorkingSet,
                                         b_TrialState->cIneq, b_TrialState->cEq,
                                         b_mLB, lb, mUB, ub, mFixed);
      expl_temp.IterDisplayQP = false;
      expl_temp.RemainFeasible = false;
      expl_temp.ProbRelTolFactor = 1.0;
      expl_temp.ConstrRelTolFactor = 1.0;
      expl_temp.PricingTolerance = 0.0;
      expl_temp.ObjectiveLimit = rtMinusInf;
      expl_temp.ConstraintTolerance = 1.0E-6;
      expl_temp.OptimalityTolerance = 2.2204460492503131E-14;
      expl_temp.StepTolerance = 1.0E-6;
      expl_temp.MaxIterations = qpoptions_MaxIterations;
      for (mLB = 0; mLB < 7; mLB++) {
        expl_temp.SolverName[mLB] = qpoptions_SolverName[mLB];
      }
      b_expl_temp = expl_temp;
      Flags.stepAccepted =
          b_step(&Flags.stepType, Hessian, lb, ub, b_TrialState, MeritFunction,
                 memspace, WorkingSet, b_QRManager, b_CholManager, QPObjective,
                 &b_expl_temp);
      if (Flags.stepAccepted) {
        for (idx_max = 0; idx_max < nVar_tmp; idx_max++) {
          b_TrialState->xstarsqp[idx_max] += b_TrialState->delta_x[idx_max];
        }
        smax = b_TrialState->cEq;
        s = anon(FcnEvaluator->objfun.workspace.load_values,
                 FcnEvaluator->objfun.workspace.cost_values,
                 FcnEvaluator->objfun.workspace.res_values,
                 FcnEvaluator->objfun.workspace.tariff_rate,
                 b_TrialState->xstarsqp);
        idx_max = 1;
        if (std::isinf(s) || std::isnan(s)) {
          if (std::isnan(s)) {
            idx_max = -3;
          } else if (s < 0.0) {
            idx_max = -1;
          } else {
            idx_max = -2;
          }
        }
        if (idx_max == 1) {
          idx_max = utils::ObjNonlinEvaluator::computeConstraints_(
              FcnEvaluator->nonlcon, b_TrialState->xstarsqp,
              b_TrialState->cIneq, &smax);
        }
        b_TrialState->sqpFval = s;
        b_TrialState->cEq = smax;
        Flags.fevalOK = (idx_max == 1);
        b_TrialState->FunctionEvaluations++;
        if (Flags.fevalOK) {
          double constrViolationIneq;
          constrViolationIneq = 0.0;
          for (idx_max = 0; idx_max < 48; idx_max++) {
            if (b_TrialState->cIneq[idx_max] > 0.0) {
              constrViolationIneq += b_TrialState->cIneq[idx_max];
            }
          }
          MeritFunction->phiFullStep =
              s + MeritFunction->penaltyParam *
                      (std::abs(smax) + constrViolationIneq);
        } else {
          MeritFunction->phiFullStep = rtInf;
        }
      }
      if ((Flags.stepType == 1) && Flags.stepAccepted && Flags.fevalOK &&
          (MeritFunction->phi < MeritFunction->phiFullStep) &&
          (b_TrialState->sqpFval < b_TrialState->sqpFval_old)) {
        Flags.stepType = 3;
        Flags.stepAccepted = false;
      } else {
        if ((Flags.stepType == 3) && Flags.stepAccepted) {
          isFeasible = true;
        } else {
          isFeasible = false;
        }
        linesearch(&Flags.fevalOK, WorkingSet->nVar, b_TrialState,
                   MeritFunction->penaltyParam, MeritFunction->phi,
                   MeritFunction->phiPrimePlus, MeritFunction->phiFullStep,
                   &FcnEvaluator->objfun, FcnEvaluator->nonlcon, isFeasible,
                   &smax, &idx_max);
        b_TrialState->steplength = smax;
        if (idx_max > 0) {
          Flags.stepAccepted = true;
        } else {
          Flags.failedLineSearch = true;
        }
      }
    }
    if (Flags.stepAccepted && (!Flags.failedLineSearch)) {
      for (idx_max = 0; idx_max < nVar_tmp; idx_max++) {
        b_TrialState->xstarsqp[idx_max] = b_TrialState->xstarsqp_old[idx_max] +
                                          b_TrialState->delta_x[idx_max];
      }
      for (idx_max = 0; idx_max <= mConstr_tmp; idx_max++) {
        b_TrialState->lambdasqp[idx_max] +=
            b_TrialState->steplength *
            (b_TrialState->lambda[idx_max] - b_TrialState->lambdasqp[idx_max]);
      }
      b_TrialState->sqpFval_old = b_TrialState->sqpFval;
      for (idxFiniteLB = 0; idxFiniteLB < 24; idxFiniteLB++) {
        b_TrialState->xstarsqp_old[idxFiniteLB] =
            b_TrialState->xstarsqp[idxFiniteLB];
        b_TrialState->grad_old[idxFiniteLB] = b_TrialState->grad[idxFiniteLB];
      }
      std::copy(&b_TrialState->cIneq[0], &b_TrialState->cIneq[48],
                &b_TrialState->cIneq_old[0]);
      b_TrialState->cEq_old = b_TrialState->cEq;
      Flags.gradOK = utils::FiniteDifferences::computeFiniteDifferences(
          FiniteDifferences, b_TrialState->sqpFval, b_TrialState->cIneq,
          b_TrialState->cEq, b_TrialState->xstarsqp, b_TrialState->grad,
          WorkingSet->Aineq, WorkingSet->Aeq, lb, ub);
      b_TrialState->FunctionEvaluations += FiniteDifferences->numEvals;
    } else {
      b_TrialState->sqpFval = b_TrialState->sqpFval_old;
      std::copy(&b_TrialState->xstarsqp_old[0], &b_TrialState->xstarsqp_old[24],
                &b_TrialState->xstarsqp[0]);
      std::copy(&b_TrialState->cIneq_old[0], &b_TrialState->cIneq_old[48],
                &b_TrialState->cIneq[0]);
      b_TrialState->cEq = b_TrialState->cEq_old;
    }
    test_exit(&Flags, memspace, MeritFunction, WorkingSet, b_TrialState,
              b_QRManager, lb, ub);
    if ((!Flags.done) && Flags.stepAccepted) {
      int iac;
      Flags.stepAccepted = false;
      Flags.stepType = 1;
      Flags.failedLineSearch = false;
      if (0 <= nVar_tmp - 1) {
        std::copy(&b_TrialState->grad[0], &b_TrialState->grad[nVar_tmp],
                  &b_TrialState->delta_gradLag[0]);
      }
      if (nVar_tmp >= 1) {
        idx_max = nVar_tmp - 1;
        for (idxFiniteLB = 0; idxFiniteLB <= idx_max; idxFiniteLB++) {
          b_TrialState->delta_gradLag[idxFiniteLB] +=
              -b_TrialState->grad_old[idxFiniteLB];
        }
      }
      for (b_mUB = 1; b_mUB <= nVar_tmp; b_mUB++) {
        b_TrialState->delta_gradLag[b_mUB - 1] +=
            WorkingSet->Aeq[b_mUB - 1] * b_TrialState->lambdasqp[mFixed];
        b_TrialState->delta_gradLag[b_mUB - 1] +=
            b_TrialState->JacCeqTrans_old[b_mUB - 1] *
            -b_TrialState->lambdasqp[mFixed];
      }
      idx_max = mFixed + 1;
      for (iac = 0; iac <= 3525; iac += 75) {
        mLB = iac + nVar_tmp;
        for (b_mUB = iac + 1; b_mUB <= mLB; b_mUB++) {
          idxFiniteLB = (b_mUB - iac) - 1;
          b_TrialState->delta_gradLag[idxFiniteLB] +=
              WorkingSet->Aineq[b_mUB - 1] * b_TrialState->lambdasqp[idx_max];
        }
        idx_max++;
      }
      idx_max = mFixed + 1;
      for (iac = 0; iac <= 3525; iac += 75) {
        mLB = iac + nVar_tmp;
        for (b_mUB = iac + 1; b_mUB <= mLB; b_mUB++) {
          idxFiniteLB = (b_mUB - iac) - 1;
          b_TrialState->delta_gradLag[idxFiniteLB] +=
              b_TrialState->JacCineqTrans_old[b_mUB - 1] *
              -b_TrialState->lambdasqp[idx_max];
        }
        idx_max++;
      }
      TrialState::saveJacobian(b_TrialState, nVar_tmp, WorkingSet->Aineq,
                               WorkingSet->Aeq);
      BFGSUpdate(nVar_tmp, Hessian, b_TrialState->delta_x,
                 b_TrialState->delta_gradLag, memspace->workspace_double);
      b_TrialState->sqpIterations++;
    }
  }
}

} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (driver.cpp)
