//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// step.cpp
//
// Code generation for function 'step'
//

// Include files
#include "step.h"
#include "SolveLP_internal_types.h"
#include "SolveLP_rtwutil.h"
#include "addAeqConstr.h"
#include "addBoundToActiveSetMatrix_.h"
#include "driver1.h"
#include "relaxed.h"
#include "rt_nonfinite.h"
#include "sortLambdaQP.h"
#include "xnrm2.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
boolean_T b_step(int *STEP_TYPE, double Hessian[576], const double lb[24],
                 const double ub[24], g_struct_T *b_TrialState,
                 d_struct_T *MeritFunction, h_struct_T *memspace,
                 c_struct_T *WorkingSet, i_struct_T *b_QRManager,
                 j_struct_T *b_CholManager, b_struct_T *QPObjective,
                 k_struct_T *qpoptions)
{
  k_struct_T b_qpoptions;
  k_struct_T c_qpoptions;
  double dv[75];
  double c;
  double constrViolation;
  int idx;
  int idx_Aineq;
  int idx_Partition;
  int nVar_tmp_tmp;
  boolean_T checkBoundViolation;
  boolean_T stepSuccess;
  stepSuccess = true;
  checkBoundViolation = true;
  nVar_tmp_tmp = WorkingSet->nVar - 1;
  if (*STEP_TYPE != 3) {
    if (0 <= nVar_tmp_tmp) {
      std::copy(&b_TrialState->xstarsqp[0],
                &b_TrialState->xstarsqp[nVar_tmp_tmp + 1],
                &b_TrialState->xstar[0]);
    }
  } else if (0 <= nVar_tmp_tmp) {
    std::copy(&b_TrialState->xstar[0], &b_TrialState->xstar[nVar_tmp_tmp + 1],
              &b_TrialState->searchDir[0]);
  }
  int exitg1;
  boolean_T guard1{false};
  do {
    int idx_lower;
    int idx_upper;
    exitg1 = 0;
    guard1 = false;
    switch (*STEP_TYPE) {
    case 1: {
      boolean_T nonlinEqRemoved;
      b_qpoptions = *qpoptions;
      c_qpoptions = *qpoptions;
      ::coder::optim::coder::qpactiveset::driver(
          Hessian, b_TrialState->grad, b_TrialState, memspace, WorkingSet,
          b_QRManager, b_CholManager, QPObjective, &b_qpoptions, &c_qpoptions);
      if (b_TrialState->state > 0) {
        double penaltyParamTrial;
        penaltyParamTrial = MeritFunction->penaltyParam;
        c = 0.0;
        for (idx = 0; idx < 48; idx++) {
          if (b_TrialState->cIneq[idx] > 0.0) {
            c += b_TrialState->cIneq[idx];
          }
        }
        constrViolation = std::abs(b_TrialState->cEq) + c;
        c = MeritFunction->linearizedConstrViol;
        MeritFunction->linearizedConstrViol = 0.0;
        c += constrViolation;
        if ((c > 2.2204460492503131E-16) && (b_TrialState->fstar > 0.0)) {
          if (b_TrialState->sqpFval == 0.0) {
            penaltyParamTrial = 1.0;
          } else {
            penaltyParamTrial = 1.5;
          }
          penaltyParamTrial = penaltyParamTrial * b_TrialState->fstar / c;
        }
        if (penaltyParamTrial < MeritFunction->penaltyParam) {
          MeritFunction->phi =
              b_TrialState->sqpFval + penaltyParamTrial * constrViolation;
          if ((MeritFunction->initFval +
               penaltyParamTrial * (MeritFunction->initConstrViolationEq +
                                    MeritFunction->initConstrViolationIneq)) -
                  MeritFunction->phi >
              static_cast<double>(MeritFunction->nPenaltyDecreases) *
                  MeritFunction->threshold) {
            MeritFunction->nPenaltyDecreases++;
            if ((MeritFunction->nPenaltyDecreases << 1) >
                b_TrialState->sqpIterations) {
              MeritFunction->threshold *= 10.0;
            }
            MeritFunction->penaltyParam = std::fmax(penaltyParamTrial, 1.0E-10);
          } else {
            MeritFunction->phi = b_TrialState->sqpFval +
                                 MeritFunction->penaltyParam * constrViolation;
          }
        } else {
          MeritFunction->penaltyParam = std::fmax(penaltyParamTrial, 1.0E-10);
          MeritFunction->phi = b_TrialState->sqpFval +
                               MeritFunction->penaltyParam * constrViolation;
        }
        MeritFunction->phiPrimePlus = std::fmin(
            b_TrialState->fstar - MeritFunction->penaltyParam * constrViolation,
            0.0);
      }
      qpactiveset::parseoutput::sortLambdaQP(
          b_TrialState->lambda, WorkingSet->nActiveConstr, WorkingSet->sizes,
          WorkingSet->isActiveIdx, WorkingSet->Wid, WorkingSet->Wlocalidx,
          memspace->workspace_double);
      nonlinEqRemoved = (WorkingSet->mEqRemoved > 0);
      while ((WorkingSet->mEqRemoved > 0) &&
             (WorkingSet->indexEqRemoved >= 1)) {
        qpactiveset::WorkingSet::addAeqConstr(WorkingSet,
                                              WorkingSet->indexEqRemoved);
        WorkingSet->mEqRemoved--;
      }
      if (nonlinEqRemoved) {
        WorkingSet->Wlocalidx[WorkingSet->sizes[0]] = 1;
      }
      if ((b_TrialState->state <= 0) && (b_TrialState->state != -6)) {
        *STEP_TYPE = 2;
      } else {
        if (0 <= nVar_tmp_tmp) {
          std::copy(&b_TrialState->xstar[0],
                    &b_TrialState->xstar[nVar_tmp_tmp + 1],
                    &b_TrialState->delta_x[0]);
        }
        guard1 = true;
      }
    } break;
    case 2:
      idx_lower = (WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1]) + 1;
      idx_Aineq = WorkingSet->nActiveConstr;
      for (idx_upper = idx_lower; idx_upper <= idx_Aineq; idx_upper++) {
        WorkingSet->isActiveConstr
            [(WorkingSet->isActiveIdx[WorkingSet->Wid[idx_upper - 1] - 1] +
              WorkingSet->Wlocalidx[idx_upper - 1]) -
             2] = false;
      }
      WorkingSet->nWConstr[2] = 0;
      WorkingSet->nWConstr[3] = 0;
      WorkingSet->nWConstr[4] = 0;
      WorkingSet->nActiveConstr =
          WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1];
      std::copy(&b_TrialState->xstar[0], &b_TrialState->xstar[75], &dv[0]);
      idx_Partition = WorkingSet->sizes[3];
      idx_Aineq = WorkingSet->sizes[4];
      for (idx = 0; idx < idx_Partition; idx++) {
        c = WorkingSet->lb[WorkingSet->indexLB[idx] - 1];
        if (-dv[WorkingSet->indexLB[idx] - 1] > c) {
          if (std::isinf(ub[WorkingSet->indexLB[idx] - 1])) {
            dv[WorkingSet->indexLB[idx] - 1] = -c + std::abs(c);
          } else {
            dv[WorkingSet->indexLB[idx] - 1] =
                (WorkingSet->ub[WorkingSet->indexLB[idx] - 1] - c) / 2.0;
          }
        }
      }
      for (idx = 0; idx < idx_Aineq; idx++) {
        c = WorkingSet->ub[WorkingSet->indexUB[idx] - 1];
        if (dv[WorkingSet->indexUB[idx] - 1] > c) {
          if (std::isinf(lb[WorkingSet->indexUB[idx] - 1])) {
            dv[WorkingSet->indexUB[idx] - 1] = c - std::abs(c);
          } else {
            dv[WorkingSet->indexUB[idx] - 1] =
                (c - WorkingSet->lb[WorkingSet->indexUB[idx] - 1]) / 2.0;
          }
        }
      }
      std::copy(&dv[0], &dv[75], &b_TrialState->xstar[0]);
      step::relaxed(Hessian, b_TrialState->grad, b_TrialState, MeritFunction,
                    memspace, WorkingSet, b_QRManager, b_CholManager,
                    QPObjective, qpoptions);
      if (0 <= nVar_tmp_tmp) {
        std::copy(&b_TrialState->xstar[0],
                  &b_TrialState->xstar[nVar_tmp_tmp + 1],
                  &b_TrialState->delta_x[0]);
      }
      guard1 = true;
      break;
    default: {
      int i;
      int i1;
      int idxIneqOffset;
      int nWIneq_old;
      int nWLower_old;
      int nWUpper_old;
      nWIneq_old = WorkingSet->nWConstr[2];
      nWLower_old = WorkingSet->nWConstr[3];
      nWUpper_old = WorkingSet->nWConstr[4];
      i = WorkingSet->nVar - 1;
      if (0 <= i) {
        std::copy(&b_TrialState->xstarsqp_old[0],
                  &b_TrialState->xstarsqp_old[i + 1],
                  &b_TrialState->xstarsqp[0]);
        std::copy(&b_TrialState->xstar[0], &b_TrialState->xstar[i + 1],
                  &b_TrialState->socDirection[0]);
      }
      std::copy(&b_TrialState->lambda[0], &b_TrialState->lambda[148],
                &b_TrialState->lambda_old[0]);
      idxIneqOffset = WorkingSet->isActiveIdx[2];
      WorkingSet->beq = -b_TrialState->cEq;
      i1 = WorkingSet->nVar;
      c = 0.0;
      for (idx_Aineq = 1; idx_Aineq <= i1; idx_Aineq++) {
        c += WorkingSet->Aeq[idx_Aineq - 1] *
             b_TrialState->searchDir[idx_Aineq - 1];
      }
      c += WorkingSet->beq;
      WorkingSet->beq = c;
      WorkingSet->bwset[WorkingSet->sizes[0]] = c;
      for (idx = 0; idx < 48; idx++) {
        WorkingSet->bineq[idx] = -b_TrialState->cIneq[idx];
      }
      for (idx_lower = 0; idx_lower <= 3525; idx_lower += 75) {
        c = 0.0;
        i1 = idx_lower + WorkingSet->nVar;
        for (idx_Aineq = idx_lower + 1; idx_Aineq <= i1; idx_Aineq++) {
          c += WorkingSet->Aineq[idx_Aineq - 1] *
               b_TrialState->searchDir[(idx_Aineq - idx_lower) - 1];
        }
        i1 = div_nde_s32_floor(idx_lower, 75);
        WorkingSet->bineq[i1] += c;
      }
      idx_Aineq = 1;
      idx_lower = 49;
      idx_upper = WorkingSet->sizes[3] + 49;
      i1 = WorkingSet->nActiveConstr;
      for (idx = idxIneqOffset; idx <= i1; idx++) {
        switch (WorkingSet->Wid[idx - 1]) {
        case 3:
          idx_Partition = idx_Aineq;
          idx_Aineq++;
          WorkingSet->bwset[idx - 1] =
              WorkingSet->bineq[WorkingSet->Wlocalidx[idx - 1] - 1];
          break;
        case 4:
          idx_Partition = idx_lower;
          idx_lower++;
          break;
        default:
          idx_Partition = idx_upper;
          idx_upper++;
          break;
        }
        b_TrialState->workingset_old[idx_Partition - 1] =
            WorkingSet->Wlocalidx[idx - 1];
      }
      if (0 <= i) {
        std::copy(&b_TrialState->xstarsqp[0], &b_TrialState->xstarsqp[i + 1],
                  &b_TrialState->xstar[0]);
      }
      std::copy(&b_TrialState->grad[0], &b_TrialState->grad[75], &dv[0]);
      b_qpoptions = *qpoptions;
      c_qpoptions = *qpoptions;
      ::coder::optim::coder::qpactiveset::driver(
          Hessian, dv, b_TrialState, memspace, WorkingSet, b_QRManager,
          b_CholManager, QPObjective, &b_qpoptions, &c_qpoptions);
      while ((WorkingSet->mEqRemoved > 0) &&
             (WorkingSet->indexEqRemoved >= 1)) {
        qpactiveset::WorkingSet::addAeqConstr(WorkingSet,
                                              WorkingSet->indexEqRemoved);
        WorkingSet->mEqRemoved--;
      }
      for (idx = 0; idx <= i; idx++) {
        c = b_TrialState->socDirection[idx];
        b_TrialState->socDirection[idx] =
            b_TrialState->xstar[idx] - b_TrialState->socDirection[idx];
        b_TrialState->xstar[idx] = c;
      }
      stepSuccess =
          (::coder::internal::blas::xnrm2(i + 1, b_TrialState->socDirection) <=
           2.0 * ::coder::internal::blas::xnrm2(i + 1, b_TrialState->xstar));
      idx_Partition = WorkingSet->sizes[3];
      WorkingSet->beq = -b_TrialState->cEq;
      WorkingSet->bwset[WorkingSet->sizes[0]] = WorkingSet->beq;
      for (idx = 0; idx < 48; idx++) {
        WorkingSet->bineq[idx] = -b_TrialState->cIneq[idx];
      }
      if (!stepSuccess) {
        idx_lower = (WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1]) + 1;
        i = WorkingSet->nActiveConstr;
        for (idx_upper = idx_lower; idx_upper <= i; idx_upper++) {
          WorkingSet->isActiveConstr
              [(WorkingSet->isActiveIdx[WorkingSet->Wid[idx_upper - 1] - 1] +
                WorkingSet->Wlocalidx[idx_upper - 1]) -
               2] = false;
        }
        WorkingSet->nWConstr[2] = 0;
        WorkingSet->nWConstr[3] = 0;
        WorkingSet->nWConstr[4] = 0;
        WorkingSet->nActiveConstr =
            WorkingSet->nWConstr[0] + WorkingSet->nWConstr[1];
        for (idx = 0; idx < nWIneq_old; idx++) {
          idx_Aineq = b_TrialState->workingset_old[idx];
          WorkingSet->nWConstr[2]++;
          WorkingSet
              ->isActiveConstr[(WorkingSet->isActiveIdx[2] + idx_Aineq) - 2] =
              true;
          WorkingSet->nActiveConstr++;
          WorkingSet->Wid[WorkingSet->nActiveConstr - 1] = 3;
          WorkingSet->Wlocalidx[WorkingSet->nActiveConstr - 1] = idx_Aineq;
          idx_lower = 75 * (idx_Aineq - 1);
          idx_upper = 75 * (WorkingSet->nActiveConstr - 1);
          i = WorkingSet->nVar - 1;
          for (idxIneqOffset = 0; idxIneqOffset <= i; idxIneqOffset++) {
            WorkingSet->ATwset[idx_upper + idxIneqOffset] =
                WorkingSet->Aineq[idx_lower + idxIneqOffset];
          }
          WorkingSet->bwset[WorkingSet->nActiveConstr - 1] =
              WorkingSet->bineq[idx_Aineq - 1];
        }
        for (idx = 0; idx < nWLower_old; idx++) {
          qpactiveset::WorkingSet::addBoundToActiveSetMatrix_(
              WorkingSet, 4, b_TrialState->workingset_old[idx + 48]);
        }
        for (idx = 0; idx < nWUpper_old; idx++) {
          qpactiveset::WorkingSet::addBoundToActiveSetMatrix_(
              WorkingSet, 5,
              b_TrialState->workingset_old[(idx + idx_Partition) + 48]);
        }
        std::copy(&b_TrialState->lambda_old[0], &b_TrialState->lambda_old[148],
                  &b_TrialState->lambda[0]);
      } else {
        qpactiveset::parseoutput::sortLambdaQP(
            b_TrialState->lambda, WorkingSet->nActiveConstr, WorkingSet->sizes,
            WorkingSet->isActiveIdx, WorkingSet->Wid, WorkingSet->Wlocalidx,
            memspace->workspace_double);
      }
      checkBoundViolation = stepSuccess;
      if (stepSuccess && (b_TrialState->state != -6)) {
        for (idx = 0; idx <= nVar_tmp_tmp; idx++) {
          b_TrialState->delta_x[idx] =
              b_TrialState->xstar[idx] + b_TrialState->socDirection[idx];
        }
      }
      guard1 = true;
    } break;
    }
    if (guard1) {
      if (b_TrialState->state != -6) {
        exitg1 = 1;
      } else {
        c = 0.0;
        constrViolation = 1.0;
        for (idx = 0; idx < 24; idx++) {
          c = std::fmax(c, std::abs(b_TrialState->grad[idx]));
          constrViolation =
              std::fmax(constrViolation, std::abs(b_TrialState->xstar[idx]));
        }
        c = std::fmax(2.2204460492503131E-16, c / constrViolation);
        for (idx_upper = 0; idx_upper < 24; idx_upper++) {
          idx_Aineq = 24 * idx_upper;
          for (idx_lower = 0; idx_lower < idx_upper; idx_lower++) {
            Hessian[idx_Aineq + idx_lower] = 0.0;
          }
          Hessian[idx_upper + 24 * idx_upper] = c;
          idx_Aineq += idx_upper;
          idx_lower = 22 - idx_upper;
          if (0 <= idx_lower) {
            std::memset(&Hessian[idx_Aineq + 1], 0,
                        (((idx_lower + idx_Aineq) - idx_Aineq) + 1) *
                            sizeof(double));
          }
        }
      }
    }
  } while (exitg1 == 0);
  if (checkBoundViolation) {
    idx_Partition = WorkingSet->sizes[3];
    idx_Aineq = WorkingSet->sizes[4];
    std::copy(&b_TrialState->delta_x[0], &b_TrialState->delta_x[75], &dv[0]);
    for (idx = 0; idx < idx_Partition; idx++) {
      c = dv[WorkingSet->indexLB[idx] - 1];
      constrViolation =
          (b_TrialState->xstarsqp[WorkingSet->indexLB[idx] - 1] + c) -
          lb[WorkingSet->indexLB[idx] - 1];
      if (constrViolation < 0.0) {
        dv[WorkingSet->indexLB[idx] - 1] = c - constrViolation;
        b_TrialState->xstar[WorkingSet->indexLB[idx] - 1] -= constrViolation;
      }
    }
    for (idx = 0; idx < idx_Aineq; idx++) {
      c = dv[WorkingSet->indexUB[idx] - 1];
      constrViolation = (ub[WorkingSet->indexUB[idx] - 1] -
                         b_TrialState->xstarsqp[WorkingSet->indexUB[idx] - 1]) -
                        c;
      if (constrViolation < 0.0) {
        dv[WorkingSet->indexUB[idx] - 1] = c + constrViolation;
        b_TrialState->xstar[WorkingSet->indexUB[idx] - 1] += constrViolation;
      }
    }
    std::copy(&dv[0], &dv[75], &b_TrialState->delta_x[0]);
  }
  return stepSuccess;
}

} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (step.cpp)
