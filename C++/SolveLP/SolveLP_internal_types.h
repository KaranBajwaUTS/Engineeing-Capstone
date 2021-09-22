//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// SolveLP_internal_types.h
//
// Code generation for function 'SolveLP'
//

#ifndef SOLVELP_INTERNAL_TYPES_H
#define SOLVELP_INTERNAL_TYPES_H

// Include files
#include "SolveLP_types.h"
#include "anonymous_function.h"
#include "rtwtypes.h"

// Type Definitions
struct b_struct_T {
  double grad[75];
  double Hx[74];
  boolean_T hasLinear;
  int nvar;
  int maxVar;
  double beta;
  double rho;
  int objtype;
  int prev_objtype;
  int prev_nvar;
  boolean_T prev_hasLinear;
  double gammaScalar;
};

struct c_struct_T {
  int mConstr;
  int mConstrOrig;
  int mConstrMax;
  int nVar;
  int nVarOrig;
  int nVarMax;
  int ldA;
  double Aineq[3600];
  double bineq[48];
  double Aeq[75];
  double beq;
  double lb[75];
  double ub[75];
  int indexLB[75];
  int indexUB[75];
  int indexFixed[75];
  int mEqRemoved;
  int indexEqRemoved;
  double ATwset[11100];
  double bwset[148];
  int nActiveConstr;
  double maxConstrWorkspace[148];
  int sizes[5];
  int sizesNormal[5];
  int sizesPhaseOne[5];
  int sizesRegularized[5];
  int sizesRegPhaseOne[5];
  int isActiveIdx[6];
  int isActiveIdxNormal[6];
  int isActiveIdxPhaseOne[6];
  int isActiveIdxRegularized[6];
  int isActiveIdxRegPhaseOne[6];
  boolean_T isActiveConstr[148];
  int Wid[148];
  int Wlocalidx[148];
  int nWConstr[5];
  int probType;
  double SLACK0;
};

struct d_struct_T {
  double penaltyParam;
  double threshold;
  int nPenaltyDecreases;
  double linearizedConstrViol;
  double initFval;
  double initConstrViolationEq;
  double initConstrViolationIneq;
  double phi;
  double phiPrimePlus;
  double phiFullStep;
  double feasRelativeFactor;
  double nlpPrimalFeasError;
  double nlpDualFeasError;
  double nlpComplError;
  double firstOrderOpt;
  boolean_T hasObjective;
};

struct e_struct_T {
  boolean_T gradOK;
  boolean_T fevalOK;
  boolean_T done;
  boolean_T stepAccepted;
  boolean_T failedLineSearch;
  int stepType;
};

struct g_struct_T {
  int nVarMax;
  int mNonlinIneq;
  int mNonlinEq;
  int mIneq;
  int mEq;
  int iNonIneq0;
  int iNonEq0;
  double sqpFval;
  double sqpFval_old;
  double xstarsqp[24];
  double xstarsqp_old[24];
  double cIneq[48];
  double cIneq_old[48];
  double cEq;
  double cEq_old;
  double grad[75];
  double grad_old[75];
  int FunctionEvaluations;
  int sqpIterations;
  int sqpExitFlag;
  double lambdasqp[148];
  double lambdasqp_old[148];
  double steplength;
  double delta_x[75];
  double socDirection[75];
  double lambda_old[148];
  int workingset_old[148];
  double JacCineqTrans_old[3600];
  double JacCeqTrans_old[75];
  double gradLag[75];
  double delta_gradLag[75];
  double xstar[75];
  double fstar;
  double firstorderopt;
  double lambda[148];
  int state;
  double maxConstr;
  int iterations;
  double searchDir[75];
};

struct h_struct_T {
  double workspace_double[11100];
  int workspace_int[148];
  int workspace_sort[148];
};

struct i_struct_T {
  int ldq;
  double QR[21904];
  double Q[21904];
  int jpvt[148];
  int mrows;
  int ncols;
  double tau[148];
  int minRowCol;
  boolean_T usedPivoting;
};

struct j_struct_T {
  double FMat[21904];
  int ldm;
  int ndims;
  int info;
  double scaleFactor;
  boolean_T ConvexCheck;
  double regTol_;
  double workspace_;
  double workspace2_;
};

struct k_struct_T {
  char SolverName[7];
  int MaxIterations;
  double StepTolerance;
  double OptimalityTolerance;
  double ConstraintTolerance;
  double ObjectiveLimit;
  double PricingTolerance;
  double ConstrRelTolFactor;
  double ProbRelTolFactor;
  boolean_T RemainFeasible;
  boolean_T IterDisplayQP;
};

struct l_struct_T {
  coder::anonymous_function objfun;
  coder::b_anonymous_function nonlcon;
  int nVar;
  int mCineq;
  int mCeq;
  boolean_T NonFiniteSupport;
  boolean_T SpecifyObjectiveGradient;
  boolean_T SpecifyConstraintGradient;
  boolean_T ScaleProblem;
};

struct m_struct_T {
  coder::anonymous_function objfun;
  coder::b_anonymous_function nonlin;
  double f_1;
  double cIneq_1[48];
  double cEq_1;
  double f_2;
  double cIneq_2[48];
  double cEq_2;
  int nVar;
  int mIneq;
  int mEq;
  int numEvals;
  boolean_T SpecifyObjectiveGradient;
  boolean_T SpecifyConstraintGradient;
  boolean_T isEmptyNonlcon;
  boolean_T hasLB[24];
  boolean_T hasUB[24];
  boolean_T hasBounds;
  int FiniteDifferenceType;
};

#endif
// End of code generation (SolveLP_internal_types.h)
