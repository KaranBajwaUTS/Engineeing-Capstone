//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// relaxed.cpp
//
// Code generation for function 'relaxed'
//

// Include files
#include "relaxed.h"
#include "SolveLP_internal_types.h"
#include "SolveLP_rtwutil.h"
#include "addBoundToActiveSetMatrix_.h"
#include "driver1.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include "sortLambdaQP.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
namespace step {
void relaxed(const double Hessian[576], const double grad[75],
             g_struct_T *b_TrialState, d_struct_T *MeritFunction,
             h_struct_T *memspace, c_struct_T *WorkingSet,
             i_struct_T *b_QRManager, j_struct_T *b_CholManager,
             b_struct_T *QPObjective, k_struct_T *qpoptions)
{
  k_struct_T b_qpoptions;
  k_struct_T c_qpoptions;
  double beta;
  double rho;
  double s;
  double smax;
  int iac;
  int idx;
  int idx_max;
  int k;
  int mLBOrig;
  int nVarOrig_tmp_tmp;
  boolean_T b_tf;
  boolean_T tf;
  nVarOrig_tmp_tmp = WorkingSet->nVar;
  beta = 0.0;
  for (idx = 0; idx < nVarOrig_tmp_tmp; idx++) {
    beta += Hessian[idx + 24 * idx];
  }
  beta /= static_cast<double>(WorkingSet->nVar);
  if (b_TrialState->sqpIterations <= 1) {
    mLBOrig = QPObjective->nvar;
    if (QPObjective->nvar < 1) {
      idx_max = 0;
    } else {
      idx_max = 1;
      if (QPObjective->nvar > 1) {
        smax = std::abs(grad[0]);
        for (k = 2; k <= mLBOrig; k++) {
          s = std::abs(grad[k - 1]);
          if (s > smax) {
            idx_max = k;
            smax = s;
          }
        }
      }
    }
    rho = 100.0 * std::fmax(1.0, std::abs(grad[idx_max - 1]));
  } else {
    mLBOrig = WorkingSet->mConstr;
    idx_max = 1;
    smax = std::abs(b_TrialState->lambdasqp[0]);
    for (k = 2; k <= mLBOrig; k++) {
      s = std::abs(b_TrialState->lambdasqp[k - 1]);
      if (s > smax) {
        idx_max = k;
        smax = s;
      }
    }
    rho = std::abs(b_TrialState->lambdasqp[idx_max - 1]);
  }
  QPObjective->nvar = WorkingSet->nVar;
  QPObjective->beta = beta;
  QPObjective->rho = rho;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 4;
  qpactiveset::WorkingSet::setProblemType(WorkingSet, 2);
  mLBOrig = WorkingSet->sizes[3];
  for (k = 0; k < 48; k++) {
    memspace->workspace_double[k] = WorkingSet->bineq[k];
    memspace->workspace_double[k] = -memspace->workspace_double[k];
  }
  for (iac = 0; iac <= 3525; iac += 75) {
    smax = 0.0;
    idx_max = iac + nVarOrig_tmp_tmp;
    for (k = iac + 1; k <= idx_max; k++) {
      smax += WorkingSet->Aineq[k - 1] * b_TrialState->xstar[(k - iac) - 1];
    }
    idx_max = div_nde_s32_floor(iac, 75);
    memspace->workspace_double[idx_max] += smax;
  }
  for (idx = 0; idx < 48; idx++) {
    b_TrialState->xstar[nVarOrig_tmp_tmp + idx] =
        static_cast<double>(memspace->workspace_double[idx] > 0.0) *
        memspace->workspace_double[idx];
    if (memspace->workspace_double[idx] <= 1.0E-6) {
      qpactiveset::WorkingSet::addBoundToActiveSetMatrix_(WorkingSet, 4,
                                                          (mLBOrig + idx) - 49);
    }
  }
  memspace->workspace_double[0] = WorkingSet->beq;
  memspace->workspace_double[0] = -memspace->workspace_double[0];
  smax = 0.0;
  for (k = 1; k <= nVarOrig_tmp_tmp; k++) {
    smax += WorkingSet->Aeq[k - 1] * b_TrialState->xstar[k - 1];
  }
  memspace->workspace_double[0] += smax;
  if (memspace->workspace_double[0] <= 0.0) {
    b_TrialState->xstar[nVarOrig_tmp_tmp + 48] = 0.0;
    b_TrialState->xstar[nVarOrig_tmp_tmp + 49] = -memspace->workspace_double[0];
    qpactiveset::WorkingSet::addBoundToActiveSetMatrix_(WorkingSet, 4,
                                                        mLBOrig - 1);
    if (memspace->workspace_double[0] >= -1.0E-6) {
      qpactiveset::WorkingSet::addBoundToActiveSetMatrix_(WorkingSet, 4,
                                                          mLBOrig);
    }
  } else {
    b_TrialState->xstar[nVarOrig_tmp_tmp + 48] = memspace->workspace_double[0];
    b_TrialState->xstar[nVarOrig_tmp_tmp + 49] = 0.0;
    qpactiveset::WorkingSet::addBoundToActiveSetMatrix_(WorkingSet, 4, mLBOrig);
    if (memspace->workspace_double[0] <= 1.0E-6) {
      qpactiveset::WorkingSet::addBoundToActiveSetMatrix_(WorkingSet, 4,
                                                          mLBOrig - 1);
    }
  }
  mLBOrig = qpoptions->MaxIterations;
  qpoptions->MaxIterations =
      (qpoptions->MaxIterations + WorkingSet->nVar) - nVarOrig_tmp_tmp;
  b_qpoptions = *qpoptions;
  c_qpoptions = *qpoptions;
  ::coder::optim::coder::qpactiveset::driver(
      Hessian, grad, b_TrialState, memspace, WorkingSet, b_QRManager,
      b_CholManager, QPObjective, &b_qpoptions, &c_qpoptions);
  qpoptions->MaxIterations = mLBOrig;
  mLBOrig = (WorkingSet->isActiveIdx[3] + WorkingSet->sizes[3]) - 51;
  tf = WorkingSet->isActiveConstr[mLBOrig + 48];
  b_tf = WorkingSet->isActiveConstr[mLBOrig + 49];
  memspace->workspace_int[0] = tf;
  memspace->workspace_int[1] = b_tf;
  iac = tf + b_tf;
  for (idx = 0; idx < 48; idx++) {
    tf = WorkingSet->isActiveConstr[mLBOrig + idx];
    memspace->workspace_int[idx + 2] = tf;
    iac += tf;
  }
  if (b_TrialState->state != -6) {
    double constrViolation;
    mLBOrig = 73 - nVarOrig_tmp_tmp;
    idx_max = nVarOrig_tmp_tmp + 1;
    smax = 0.0;
    s = 0.0;
    if (74 - nVarOrig_tmp_tmp >= 1) {
      for (k = idx_max; k < 75; k++) {
        smax += std::abs(b_TrialState->xstar[k - 1]);
      }
      for (k = 0; k <= mLBOrig; k++) {
        constrViolation = b_TrialState->xstar[nVarOrig_tmp_tmp + k];
        s += constrViolation * constrViolation;
      }
    }
    rho = (b_TrialState->fstar - rho * smax) - beta / 2.0 * s;
    beta = MeritFunction->penaltyParam;
    smax = 0.0;
    for (idx = 0; idx < 48; idx++) {
      if (b_TrialState->cIneq[idx] > 0.0) {
        smax += b_TrialState->cIneq[idx];
      }
    }
    constrViolation = std::abs(b_TrialState->cEq) + smax;
    smax = MeritFunction->linearizedConstrViol;
    s = 0.0;
    if (74 - nVarOrig_tmp_tmp >= 1) {
      for (k = idx_max; k < 75; k++) {
        s += std::abs(b_TrialState->xstar[k - 1]);
      }
    }
    MeritFunction->linearizedConstrViol = s;
    smax = (constrViolation + smax) - s;
    if ((smax > 2.2204460492503131E-16) && (rho > 0.0)) {
      if (b_TrialState->sqpFval == 0.0) {
        beta = 1.0;
      } else {
        beta = 1.5;
      }
      beta = beta * rho / smax;
    }
    if (beta < MeritFunction->penaltyParam) {
      MeritFunction->phi = b_TrialState->sqpFval + beta * constrViolation;
      if ((MeritFunction->initFval +
           beta * (MeritFunction->initConstrViolationEq +
                   MeritFunction->initConstrViolationIneq)) -
              MeritFunction->phi >
          static_cast<double>(MeritFunction->nPenaltyDecreases) *
              MeritFunction->threshold) {
        MeritFunction->nPenaltyDecreases++;
        if ((MeritFunction->nPenaltyDecreases << 1) >
            b_TrialState->sqpIterations) {
          MeritFunction->threshold *= 10.0;
        }
        MeritFunction->penaltyParam = std::fmax(beta, 1.0E-10);
      } else {
        MeritFunction->phi = b_TrialState->sqpFval +
                             MeritFunction->penaltyParam * constrViolation;
      }
    } else {
      MeritFunction->penaltyParam = std::fmax(beta, 1.0E-10);
      MeritFunction->phi =
          b_TrialState->sqpFval + MeritFunction->penaltyParam * constrViolation;
    }
    MeritFunction->phiPrimePlus =
        std::fmin(rho - MeritFunction->penaltyParam * constrViolation, 0.0);
    mLBOrig = WorkingSet->isActiveIdx[1] - 1;
    if ((memspace->workspace_int[0] != 0) &&
        (memspace->workspace_int[1] != 0)) {
      tf = true;
    } else {
      tf = false;
    }
    b_TrialState->lambda[mLBOrig] *= static_cast<double>(tf);
    mLBOrig = WorkingSet->isActiveIdx[2];
    idx_max = WorkingSet->nActiveConstr;
    for (idx = mLBOrig; idx <= idx_max; idx++) {
      if (WorkingSet->Wid[idx - 1] == 3) {
        b_TrialState->lambda[idx - 1] *= static_cast<double>(
            memspace->workspace_int[WorkingSet->Wlocalidx[idx - 1] + 1]);
      }
    }
  }
  idx = WorkingSet->nActiveConstr - 1;
  while ((idx + 1 > WorkingSet->sizes[0] + 1) && (iac > 0)) {
    if ((WorkingSet->Wid[idx] == 4) &&
        (WorkingSet->Wlocalidx[idx] > WorkingSet->sizes[3] - 50)) {
      smax = b_TrialState->lambda[WorkingSet->nActiveConstr - 1];
      b_TrialState->lambda[WorkingSet->nActiveConstr - 1] = 0.0;
      b_TrialState->lambda[idx] = smax;
      mLBOrig = WorkingSet->Wid[idx] - 1;
      WorkingSet
          ->isActiveConstr[(WorkingSet->isActiveIdx[WorkingSet->Wid[idx] - 1] +
                            WorkingSet->Wlocalidx[idx]) -
                           2] = false;
      WorkingSet->Wid[idx] = WorkingSet->Wid[WorkingSet->nActiveConstr - 1];
      WorkingSet->Wlocalidx[idx] =
          WorkingSet->Wlocalidx[WorkingSet->nActiveConstr - 1];
      idx_max = WorkingSet->nVar;
      for (k = 0; k < idx_max; k++) {
        WorkingSet->ATwset[k + 75 * idx] =
            WorkingSet->ATwset[k + 75 * (WorkingSet->nActiveConstr - 1)];
      }
      WorkingSet->bwset[idx] = WorkingSet->bwset[WorkingSet->nActiveConstr - 1];
      WorkingSet->nActiveConstr--;
      WorkingSet->nWConstr[mLBOrig]--;
      iac--;
    }
    idx--;
  }
  QPObjective->nvar = nVarOrig_tmp_tmp;
  QPObjective->hasLinear = true;
  QPObjective->objtype = 3;
  qpactiveset::WorkingSet::setProblemType(WorkingSet, 3);
  qpactiveset::parseoutput::sortLambdaQP(
      b_TrialState->lambda, WorkingSet->nActiveConstr, WorkingSet->sizes,
      WorkingSet->isActiveIdx, WorkingSet->Wid, WorkingSet->Wlocalidx,
      memspace->workspace_double);
}

} // namespace step
} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (relaxed.cpp)
