//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// factoryConstruct.cpp
//
// Code generation for function 'factoryConstruct'
//

// Include files
#include "factoryConstruct.h"
#include "SolveLP_internal_types.h"
#include "anonymous_function.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace utils {
namespace FiniteDifferences {
void factoryConstruct(const anonymous_function *objfun,
                      const b_anonymous_function nonlin, const double lb[24],
                      const double ub[24], m_struct_T *obj)
{
  int idx;
  boolean_T b;
  obj->objfun = *objfun;
  obj->nonlin = nonlin;
  obj->f_1 = 0.0;
  obj->f_2 = 0.0;
  obj->nVar = 24;
  obj->mIneq = 48;
  obj->mEq = 1;
  obj->numEvals = 0;
  obj->SpecifyObjectiveGradient = false;
  obj->SpecifyConstraintGradient = false;
  obj->isEmptyNonlcon = false;
  obj->FiniteDifferenceType = 0;
  b = false;
  idx = 0;
  while ((!b) && (idx + 1 <= 24)) {
    obj->hasLB[idx] = ((!std::isinf(lb[idx])) && (!std::isnan(lb[idx])));
    obj->hasUB[idx] = ((!std::isinf(ub[idx])) && (!std::isnan(ub[idx])));
    if (obj->hasLB[idx] || obj->hasUB[idx]) {
      b = true;
    }
    idx++;
  }
  while (idx + 1 <= 24) {
    obj->hasLB[idx] = ((!std::isinf(lb[idx])) && (!std::isnan(lb[idx])));
    obj->hasUB[idx] = ((!std::isinf(ub[idx])) && (!std::isnan(ub[idx])));
    idx++;
  }
  obj->hasBounds = b;
}

} // namespace FiniteDifferences
} // namespace utils
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (factoryConstruct.cpp)
