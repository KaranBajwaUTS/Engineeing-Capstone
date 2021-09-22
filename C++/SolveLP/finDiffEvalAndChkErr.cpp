//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// finDiffEvalAndChkErr.cpp
//
// Code generation for function 'finDiffEvalAndChkErr'
//

// Include files
#include "finDiffEvalAndChkErr.h"
#include "SolveLP.h"
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
namespace internal {
boolean_T finDiffEvalAndChkErr(const anonymous_function *obj_objfun,
                               const b_anonymous_function obj_nonlin,
                               double *fplus, double cIneqPlus[48],
                               double *cEqPlus, int dim, double delta,
                               double xk[24])
{
  double temp_tmp;
  boolean_T evalOK;
  temp_tmp = xk[dim - 1];
  xk[dim - 1] = temp_tmp + delta;
  *fplus = anon(
      obj_objfun->workspace.load_values, obj_objfun->workspace.cost_values,
      obj_objfun->workspace.res_values, obj_objfun->workspace.tariff_rate, xk);
  evalOK = ((!std::isinf(*fplus)) && (!std::isnan(*fplus)));
  if (evalOK) {
    int idx;
    anon(obj_nonlin.workspace.battery_size,
         obj_nonlin.workspace.battery_initial_soc,
         obj_nonlin.workspace.battery_minimum_soc,
         obj_nonlin.workspace.battery_maximum_soc, xk, cIneqPlus, cEqPlus);
    idx = 0;
    while (evalOK && (idx + 1 <= 48)) {
      evalOK = ((!std::isinf(cIneqPlus[idx])) && (!std::isnan(cIneqPlus[idx])));
      idx++;
    }
    if (evalOK) {
      idx = 1;
      while (evalOK && (idx <= 1)) {
        evalOK = ((!std::isinf(*cEqPlus)) && (!std::isnan(*cEqPlus)));
        idx = 2;
      }
      xk[dim - 1] = temp_tmp;
    }
  }
  return evalOK;
}

} // namespace internal
} // namespace FiniteDifferences
} // namespace utils
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (finDiffEvalAndChkErr.cpp)
