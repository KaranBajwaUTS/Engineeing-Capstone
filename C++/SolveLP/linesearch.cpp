//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// linesearch.cpp
//
// Code generation for function 'linesearch'
//

// Include files
#include "linesearch.h"
#include "SolveLP.h"
#include "SolveLP_internal_types.h"
#include "anonymous_function.h"
#include "computeConstraints_.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
void linesearch(boolean_T *evalWellDefined, int WorkingSet_nVar,
                g_struct_T *b_TrialState, double MeritFunction_penaltyParam,
                double MeritFunction_phi, double MeritFunction_phiPrimePlus,
                double MeritFunction_phiFullStep,
                const anonymous_function *FcnEvaluator_objfun,
                const b_anonymous_function FcnEvaluator_nonlcon,
                boolean_T socTaken, double *alpha, int *exitflag)
{
  double phi_alpha;
  *alpha = 1.0;
  *exitflag = 1;
  phi_alpha = MeritFunction_phiFullStep;
  if (0 <= WorkingSet_nVar - 1) {
    std::copy(&b_TrialState->delta_x[0],
              &b_TrialState->delta_x[WorkingSet_nVar],
              &b_TrialState->searchDir[0]);
  }
  int exitg1;
  do {
    exitg1 = 0;
    if (b_TrialState->FunctionEvaluations < 2400) {
      if ((*evalWellDefined) &&
          (phi_alpha <=
           MeritFunction_phi + *alpha * 0.0001 * MeritFunction_phiPrimePlus)) {
        exitg1 = 1;
      } else {
        int ixlast;
        boolean_T exitg2;
        boolean_T tooSmallX;
        *alpha *= 0.7;
        for (ixlast = 0; ixlast < WorkingSet_nVar; ixlast++) {
          b_TrialState->delta_x[ixlast] = *alpha * b_TrialState->xstar[ixlast];
        }
        if (socTaken) {
          phi_alpha = *alpha * *alpha;
          if ((WorkingSet_nVar >= 1) && (!(phi_alpha == 0.0))) {
            ixlast = WorkingSet_nVar - 1;
            for (int k{0}; k <= ixlast; k++) {
              b_TrialState->delta_x[k] +=
                  phi_alpha * b_TrialState->socDirection[k];
            }
          }
        }
        tooSmallX = true;
        ixlast = 0;
        exitg2 = false;
        while ((!exitg2) && (ixlast <= WorkingSet_nVar - 1)) {
          if (1.0E-6 *
                  std::fmax(1.0, std::abs(b_TrialState->xstarsqp[ixlast])) <=
              std::abs(b_TrialState->delta_x[ixlast])) {
            tooSmallX = false;
            exitg2 = true;
          } else {
            ixlast++;
          }
        }
        if (tooSmallX) {
          *exitflag = -2;
          exitg1 = 1;
        } else {
          double fval;
          for (ixlast = 0; ixlast < WorkingSet_nVar; ixlast++) {
            b_TrialState->xstarsqp[ixlast] =
                b_TrialState->xstarsqp_old[ixlast] +
                b_TrialState->delta_x[ixlast];
          }
          phi_alpha = b_TrialState->cEq;
          fval = anon(FcnEvaluator_objfun->workspace.load_values,
                      FcnEvaluator_objfun->workspace.cost_values,
                      FcnEvaluator_objfun->workspace.res_values,
                      FcnEvaluator_objfun->workspace.tariff_rate,
                      b_TrialState->xstarsqp);
          ixlast = 1;
          if (std::isinf(fval) || std::isnan(fval)) {
            if (std::isnan(fval)) {
              ixlast = -3;
            } else if (fval < 0.0) {
              ixlast = -1;
            } else {
              ixlast = -2;
            }
          }
          if (ixlast == 1) {
            ixlast = utils::ObjNonlinEvaluator::computeConstraints_(
                FcnEvaluator_nonlcon, b_TrialState->xstarsqp,
                b_TrialState->cIneq, &phi_alpha);
          }
          b_TrialState->sqpFval = fval;
          b_TrialState->cEq = phi_alpha;
          b_TrialState->FunctionEvaluations++;
          *evalWellDefined = (ixlast == 1);
          if (*evalWellDefined) {
            double constrViolationIneq;
            constrViolationIneq = 0.0;
            for (ixlast = 0; ixlast < 48; ixlast++) {
              if (b_TrialState->cIneq[ixlast] > 0.0) {
                constrViolationIneq += b_TrialState->cIneq[ixlast];
              }
            }
            phi_alpha = fval + MeritFunction_penaltyParam *
                                   (std::abs(phi_alpha) + constrViolationIneq);
          } else {
            phi_alpha = rtInf;
          }
        }
      }
    } else {
      *exitflag = 0;
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (linesearch.cpp)
