//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// fmincon.cpp
//
// Code generation for function 'fmincon'
//

// Include files
#include "fmincon.h"
#include "SolveLP.h"
#include "SolveLP_internal_types.h"
#include "anonymous_function.h"
#include "computeConstraints_.h"
#include "computeFiniteDifferences.h"
#include "driver.h"
#include "factoryConstruct.h"
#include "loadProblem.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
void fmincon(const anonymous_function *fun, const double x0[24],
             const double lb[24], const double ub[24],
             const b_anonymous_function nonlcon, double x[24])
{
  static c_struct_T WorkingSet;
  static h_struct_T memspace;
  static i_struct_T s;
  static j_struct_T CholManager;
  b_struct_T QPObjective;
  d_struct_T MeritFunction;
  g_struct_T TrialState;
  l_struct_T FcnEvaluator;
  m_struct_T FiniteDifferences;
  double Hessian[576];
  double Ceq_workspace;
  double d;
  double fval;
  int b_i;
  int colOffsetATw;
  int i;
  int iATw0;
  int idx;
  int mFixed;
  TrialState.nVarMax = 75;
  TrialState.mNonlinIneq = 48;
  TrialState.mNonlinEq = 1;
  TrialState.mIneq = 48;
  TrialState.mEq = 1;
  TrialState.iNonIneq0 = 1;
  TrialState.iNonEq0 = 1;
  TrialState.sqpFval_old = 0.0;
  TrialState.sqpIterations = 0;
  TrialState.sqpExitFlag = 0;
  std::memset(&TrialState.lambdasqp[0], 0, 148U * sizeof(double));
  TrialState.steplength = 1.0;
  std::memset(&TrialState.delta_x[0], 0, 75U * sizeof(double));
  TrialState.fstar = 0.0;
  TrialState.firstorderopt = 0.0;
  std::memset(&TrialState.lambda[0], 0, 148U * sizeof(double));
  TrialState.state = 0;
  TrialState.maxConstr = 0.0;
  TrialState.iterations = 0;
  std::copy(&x0[0], &x0[24], &TrialState.xstarsqp[0]);
  FcnEvaluator.objfun = *fun;
  FcnEvaluator.nonlcon = nonlcon;
  FcnEvaluator.nVar = 24;
  FcnEvaluator.mCineq = 48;
  FcnEvaluator.mCeq = 1;
  FcnEvaluator.NonFiniteSupport = true;
  FcnEvaluator.SpecifyObjectiveGradient = false;
  FcnEvaluator.SpecifyConstraintGradient = false;
  FcnEvaluator.ScaleProblem = false;
  WorkingSet.mConstr = 0;
  WorkingSet.mConstrOrig = 0;
  WorkingSet.mConstrMax = 148;
  WorkingSet.nVar = 24;
  WorkingSet.nVarOrig = 24;
  WorkingSet.nVarMax = 75;
  WorkingSet.ldA = 75;
  std::memset(&WorkingSet.Aineq[0], 0, 3600U * sizeof(double));
  std::memset(&WorkingSet.bineq[0], 0, 48U * sizeof(double));
  WorkingSet.beq = 0.0;
  std::memset(&WorkingSet.Aeq[0], 0, 75U * sizeof(double));
  std::memset(&WorkingSet.lb[0], 0, 75U * sizeof(double));
  std::memset(&WorkingSet.ub[0], 0, 75U * sizeof(double));
  WorkingSet.mEqRemoved = 0;
  WorkingSet.indexEqRemoved = 0;
  std::memset(&WorkingSet.ATwset[0], 0, 11100U * sizeof(double));
  WorkingSet.nActiveConstr = 0;
  std::memset(&WorkingSet.bwset[0], 0, 148U * sizeof(double));
  std::memset(&WorkingSet.maxConstrWorkspace[0], 0, 148U * sizeof(double));
  for (i = 0; i < 5; i++) {
    WorkingSet.sizes[i] = 0;
    WorkingSet.sizesNormal[i] = 0;
    WorkingSet.sizesPhaseOne[i] = 0;
    WorkingSet.sizesRegularized[i] = 0;
    WorkingSet.sizesRegPhaseOne[i] = 0;
  }
  for (i = 0; i < 6; i++) {
    WorkingSet.isActiveIdx[i] = 0;
    WorkingSet.isActiveIdxNormal[i] = 0;
    WorkingSet.isActiveIdxPhaseOne[i] = 0;
    WorkingSet.isActiveIdxRegularized[i] = 0;
    WorkingSet.isActiveIdxRegPhaseOne[i] = 0;
  }
  std::memset(&WorkingSet.isActiveConstr[0], 0, 148U * sizeof(boolean_T));
  std::memset(&WorkingSet.Wid[0], 0, 148U * sizeof(int));
  std::memset(&WorkingSet.Wlocalidx[0], 0, 148U * sizeof(int));
  for (i = 0; i < 5; i++) {
    WorkingSet.nWConstr[i] = 0;
  }
  WorkingSet.probType = 3;
  WorkingSet.SLACK0 = 1.0E-5;
  std::memset(&WorkingSet.indexLB[0], 0, 75U * sizeof(int));
  std::memset(&WorkingSet.indexUB[0], 0, 75U * sizeof(int));
  std::memset(&WorkingSet.indexFixed[0], 0, 75U * sizeof(int));
  iATw0 = -1;
  colOffsetATw = -1;
  mFixed = 0;
  for (idx = 0; idx < 24; idx++) {
    boolean_T guard1{false};
    d = lb[idx];
    guard1 = false;
    if ((!std::isinf(d)) && (!std::isnan(d))) {
      if (std::abs(d - ub[idx]) < 1.0E-6) {
        mFixed++;
        WorkingSet.indexFixed[mFixed - 1] = idx + 1;
      } else {
        iATw0++;
        WorkingSet.indexLB[iATw0] = idx + 1;
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      d = ub[idx];
      if ((!std::isinf(d)) && (!std::isnan(d))) {
        colOffsetATw++;
        WorkingSet.indexUB[colOffsetATw] = idx + 1;
      }
    }
  }
  optim::coder::qpactiveset::WorkingSet::loadProblem(&WorkingSet, iATw0 + 1,
                                                     colOffsetATw + 1, mFixed);
  for (idx = 0; idx <= iATw0; idx++) {
    b_i = WorkingSet.indexLB[idx];
    TrialState.xstarsqp[b_i - 1] =
        std::fmax(TrialState.xstarsqp[b_i - 1], lb[b_i - 1]);
  }
  for (idx = 0; idx <= colOffsetATw; idx++) {
    b_i = WorkingSet.indexUB[idx];
    TrialState.xstarsqp[b_i - 1] =
        std::fmin(TrialState.xstarsqp[b_i - 1], ub[b_i - 1]);
  }
  for (idx = 0; idx < mFixed; idx++) {
    b_i = WorkingSet.indexFixed[idx];
    TrialState.xstarsqp[b_i - 1] = ub[b_i - 1];
  }
  Ceq_workspace = TrialState.cEq;
  fval = anon(fun->workspace.load_values, fun->workspace.cost_values,
              fun->workspace.res_values, fun->workspace.tariff_rate,
              TrialState.xstarsqp);
  if ((!std::isinf(fval)) && (!std::isnan(fval))) {
    optim::coder::utils::ObjNonlinEvaluator::computeConstraints_(
        nonlcon, TrialState.xstarsqp, TrialState.cIneq, &Ceq_workspace);
  }
  TrialState.sqpFval = fval;
  TrialState.cEq = Ceq_workspace;
  optim::coder::utils::FiniteDifferences::factoryConstruct(fun, nonlcon, lb, ub,
                                                           &FiniteDifferences);
  optim::coder::utils::FiniteDifferences::computeFiniteDifferences(
      &FiniteDifferences, fval, TrialState.cIneq, Ceq_workspace,
      TrialState.xstarsqp, TrialState.grad, WorkingSet.Aineq, WorkingSet.Aeq,
      lb, ub);
  TrialState.FunctionEvaluations = FiniteDifferences.numEvals + 1;
  WorkingSet.beq = -Ceq_workspace;
  WorkingSet.bwset[mFixed] = -Ceq_workspace;
  i = 75 * mFixed;
  std::copy(&WorkingSet.Aeq[0], &WorkingSet.Aeq[24], &WorkingSet.ATwset[i]);
  for (idx = 0; idx < 48; idx++) {
    WorkingSet.bineq[idx] = -TrialState.cIneq[idx];
  }
  for (idx = 0; idx <= iATw0; idx++) {
    WorkingSet.lb[WorkingSet.indexLB[idx] - 1] =
        -lb[WorkingSet.indexLB[idx] - 1] + x0[WorkingSet.indexLB[idx] - 1];
  }
  for (idx = 0; idx <= colOffsetATw; idx++) {
    WorkingSet.ub[WorkingSet.indexUB[idx] - 1] =
        ub[WorkingSet.indexUB[idx] - 1] - x0[WorkingSet.indexUB[idx] - 1];
  }
  for (idx = 0; idx < mFixed; idx++) {
    d = ub[WorkingSet.indexFixed[idx] - 1] - x0[WorkingSet.indexFixed[idx] - 1];
    WorkingSet.ub[WorkingSet.indexFixed[idx] - 1] = d;
    WorkingSet.bwset[idx] = d;
  }
  optim::coder::qpactiveset::WorkingSet::setProblemType(&WorkingSet, 3);
  i = WorkingSet.isActiveIdx[2];
  for (idx = i; idx < 149; idx++) {
    WorkingSet.isActiveConstr[idx - 1] = false;
  }
  WorkingSet.nWConstr[0] = WorkingSet.sizes[0];
  WorkingSet.nWConstr[1] = 1;
  WorkingSet.nWConstr[2] = 0;
  WorkingSet.nWConstr[3] = 0;
  WorkingSet.nWConstr[4] = 0;
  WorkingSet.nActiveConstr = WorkingSet.nWConstr[0] + 1;
  i = WorkingSet.sizes[0];
  for (iATw0 = 0; iATw0 < i; iATw0++) {
    WorkingSet.Wid[iATw0] = 1;
    WorkingSet.Wlocalidx[iATw0] = iATw0 + 1;
    WorkingSet.isActiveConstr[iATw0] = true;
    colOffsetATw = 75 * iATw0;
    b_i = WorkingSet.indexFixed[iATw0];
    if (0 <= b_i - 2) {
      std::memset(&WorkingSet.ATwset[colOffsetATw], 0,
                  (((b_i + colOffsetATw) - colOffsetATw) + -1) *
                      sizeof(double));
    }
    WorkingSet.ATwset[(WorkingSet.indexFixed[iATw0] + colOffsetATw) - 1] = 1.0;
    b_i = WorkingSet.indexFixed[iATw0] + 1;
    mFixed = WorkingSet.nVar;
    if (b_i <= mFixed) {
      std::memset(&WorkingSet.ATwset[(b_i + colOffsetATw) + -1], 0,
                  ((((mFixed + colOffsetATw) - b_i) - colOffsetATw) + 1) *
                      sizeof(double));
    }
    WorkingSet.bwset[iATw0] = WorkingSet.ub[WorkingSet.indexFixed[iATw0] - 1];
  }
  WorkingSet.Wid[WorkingSet.sizes[0]] = 2;
  WorkingSet.Wlocalidx[WorkingSet.sizes[0]] = 1;
  WorkingSet.isActiveConstr[WorkingSet.sizes[0]] = true;
  iATw0 = 75 * WorkingSet.sizes[0];
  b_i = WorkingSet.nVar - 1;
  WorkingSet.bwset[WorkingSet.sizes[0]] = WorkingSet.beq;
  for (i = 0; i <= b_i; i++) {
    WorkingSet.ATwset[iATw0 + i] = WorkingSet.Aeq[i];
  }
  MeritFunction.initFval = fval;
  MeritFunction.penaltyParam = 1.0;
  MeritFunction.threshold = 0.0001;
  MeritFunction.nPenaltyDecreases = 0;
  MeritFunction.linearizedConstrViol = 0.0;
  MeritFunction.initConstrViolationEq = std::abs(Ceq_workspace);
  Ceq_workspace = 0.0;
  for (idx = 0; idx < 48; idx++) {
    d = TrialState.cIneq[idx];
    if (d > 0.0) {
      Ceq_workspace += d;
    }
  }
  MeritFunction.initConstrViolationIneq = Ceq_workspace;
  MeritFunction.phi = 0.0;
  MeritFunction.phiPrimePlus = 0.0;
  MeritFunction.phiFullStep = 0.0;
  MeritFunction.feasRelativeFactor = 0.0;
  MeritFunction.nlpPrimalFeasError = 0.0;
  MeritFunction.nlpDualFeasError = 0.0;
  MeritFunction.nlpComplError = 0.0;
  MeritFunction.firstOrderOpt = 0.0;
  MeritFunction.hasObjective = true;
  s.ldq = 148;
  std::memset(&s.QR[0], 0, 21904U * sizeof(double));
  std::memset(&s.Q[0], 0, 21904U * sizeof(double));
  s.mrows = 0;
  s.ncols = 0;
  std::memset(&s.jpvt[0], 0, 148U * sizeof(int));
  std::memset(&s.tau[0], 0, 148U * sizeof(double));
  s.minRowCol = 0;
  s.usedPivoting = false;
  std::memset(&QPObjective.grad[0], 0, 75U * sizeof(double));
  std::memset(&QPObjective.Hx[0], 0, 74U * sizeof(double));
  QPObjective.hasLinear = true;
  QPObjective.nvar = 24;
  QPObjective.maxVar = 75;
  QPObjective.beta = 0.0;
  QPObjective.rho = 0.0;
  QPObjective.objtype = 3;
  QPObjective.prev_objtype = 3;
  QPObjective.prev_nvar = 0;
  QPObjective.prev_hasLinear = false;
  QPObjective.gammaScalar = 0.0;
  optim::coder::fminconsqp::driver(
      lb, ub, &TrialState, &MeritFunction, &FcnEvaluator, &FiniteDifferences,
      &memspace, &WorkingSet, &s, &QPObjective, Hessian, &CholManager);
  std::copy(&TrialState.xstarsqp[0], &TrialState.xstarsqp[24], &x[0]);
}

} // namespace coder

// End of code generation (fmincon.cpp)
