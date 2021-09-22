//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// computeDualFeasError.cpp
//
// Code generation for function 'computeDualFeasError'
//

// Include files
#include "computeDualFeasError.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
namespace stopping {
void computeDualFeasError(int nVar, const double gradLag[75], boolean_T *gradOK,
                          double *val)
{
  int idx;
  boolean_T exitg1;
  *gradOK = true;
  *val = 0.0;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx <= nVar - 1)) {
    *gradOK = ((!std::isinf(gradLag[idx])) && (!std::isnan(gradLag[idx])));
    if (!*gradOK) {
      exitg1 = true;
    } else {
      *val = std::fmax(*val, std::abs(gradLag[idx]));
      idx++;
    }
  }
}

} // namespace stopping
} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (computeDualFeasError.cpp)
