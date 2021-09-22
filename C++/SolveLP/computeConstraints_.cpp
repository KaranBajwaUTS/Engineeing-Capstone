//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// computeConstraints_.cpp
//
// Code generation for function 'computeConstraints_'
//

// Include files
#include "computeConstraints_.h"
#include "SolveLP.h"
#include "anonymous_function.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace utils {
namespace ObjNonlinEvaluator {
int computeConstraints_(const b_anonymous_function obj_nonlcon,
                        const double x[24], double Cineq_workspace[48],
                        double *Ceq_workspace)
{
  double varargout_1[48];
  double d;
  int idx_current;
  int status;
  boolean_T allFinite;
  anon(obj_nonlcon.workspace.battery_size,
       obj_nonlcon.workspace.battery_initial_soc,
       obj_nonlcon.workspace.battery_minimum_soc,
       obj_nonlcon.workspace.battery_maximum_soc, x, varargout_1, &d);
  std::copy(&varargout_1[0], &varargout_1[48], &Cineq_workspace[0]);
  *Ceq_workspace = d;
  status = 1;
  allFinite = true;
  idx_current = 0;
  while (allFinite && (idx_current + 1 <= 48)) {
    allFinite = ((!std::isinf(Cineq_workspace[idx_current])) &&
                 (!std::isnan(Cineq_workspace[idx_current])));
    idx_current++;
  }
  if (!allFinite) {
    idx_current--;
    if (std::isnan(Cineq_workspace[idx_current])) {
      status = -3;
    } else if (Cineq_workspace[idx_current] < 0.0) {
      status = -1;
    } else {
      status = -2;
    }
  } else {
    allFinite = true;
    idx_current = 1;
    while (allFinite && (idx_current <= 1)) {
      allFinite =
          ((!std::isinf(*Ceq_workspace)) && (!std::isnan(*Ceq_workspace)));
      idx_current = 2;
    }
    if (!allFinite) {
      if (std::isnan(d)) {
        status = -3;
      } else if (d < 0.0) {
        status = -1;
      } else {
        status = -2;
      }
    }
  }
  return status;
}

} // namespace ObjNonlinEvaluator
} // namespace utils
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (computeConstraints_.cpp)
