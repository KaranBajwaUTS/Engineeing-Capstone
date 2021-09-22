//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// computeFiniteDifferences.cpp
//
// Code generation for function 'computeFiniteDifferences'
//

// Include files
#include "computeFiniteDifferences.h"
#include "SolveLP_internal_types.h"
#include "anonymous_function.h"
#include "finDiffEvalAndChkErr.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace utils {
namespace FiniteDifferences {
boolean_T computeFiniteDifferences(m_struct_T *obj, double fCurrent,
                                   const double cIneqCurrent[48],
                                   double cEqCurrent, double xk[24],
                                   double gradf[75], double JacCineqTrans[3600],
                                   double JacCeqTrans[75], const double lb[24],
                                   const double ub[24])
{
  int idx;
  boolean_T evalOK;
  boolean_T exitg1;
  evalOK = true;
  obj->numEvals = 0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx < 24)) {
    double deltaX;
    boolean_T guard1{false};
    boolean_T modifiedStep;
    modifiedStep = false;
    deltaX = 1.4901161193847656E-8 *
             (1.0 - 2.0 * static_cast<double>(xk[idx] < 0.0)) *
             std::fmax(std::abs(xk[idx]), 1.0);
    if (obj->hasLB[idx] || obj->hasUB[idx]) {
      if (obj->hasLB[idx] && obj->hasUB[idx]) {
        double ubDiff;
        ubDiff = deltaX;
        if ((lb[idx] != ub[idx]) && (xk[idx] >= lb[idx]) &&
            (xk[idx] <= ub[idx]) &&
            ((xk[idx] + deltaX > ub[idx]) || (xk[idx] + deltaX < lb[idx]))) {
          ubDiff = -deltaX;
          modifiedStep = true;
          deltaX = xk[idx] + -deltaX;
          if ((deltaX > ub[idx]) || (deltaX < lb[idx])) {
            deltaX = xk[idx] - lb[idx];
            ubDiff = ub[idx] - xk[idx];
            if (deltaX <= ubDiff) {
              ubDiff = -deltaX;
            }
          }
        }
        deltaX = ubDiff;
      } else if (obj->hasUB[idx]) {
        if ((xk[idx] <= ub[idx]) && (xk[idx] + deltaX > ub[idx])) {
          deltaX = -deltaX;
          modifiedStep = true;
        }
      } else if ((xk[idx] >= lb[idx]) && (xk[idx] + deltaX < lb[idx])) {
        deltaX = -deltaX;
        modifiedStep = true;
      }
    }
    evalOK = internal::finDiffEvalAndChkErr(&obj->objfun, obj->nonlin,
                                            &obj->f_1, obj->cIneq_1,
                                            &obj->cEq_1, idx + 1, deltaX, xk);
    obj->numEvals++;
    guard1 = false;
    if (!evalOK) {
      if (!modifiedStep) {
        deltaX = -deltaX;
        if (obj->hasLB[idx] && (xk[idx] + deltaX >= lb[idx]) &&
            obj->hasUB[idx] && (xk[idx] + deltaX <= ub[idx])) {
          modifiedStep = true;
        } else {
          modifiedStep = false;
        }
        if ((!obj->hasBounds) || modifiedStep) {
          evalOK = internal::finDiffEvalAndChkErr(
              &obj->objfun, obj->nonlin, &obj->f_1, obj->cIneq_1, &obj->cEq_1,
              idx + 1, deltaX, xk);
          obj->numEvals++;
        }
      }
      if (!evalOK) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      gradf[idx] = (obj->f_1 - fCurrent) / deltaX;
      for (int idx_row{0}; idx_row < 48; idx_row++) {
        JacCineqTrans[idx + 75 * idx_row] =
            (obj->cIneq_1[idx_row] - cIneqCurrent[idx_row]) / deltaX;
      }
      JacCeqTrans[idx] = (obj->cEq_1 - cEqCurrent) / deltaX;
      idx++;
    }
  }
  return evalOK;
}

} // namespace FiniteDifferences
} // namespace utils
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (computeFiniteDifferences.cpp)
