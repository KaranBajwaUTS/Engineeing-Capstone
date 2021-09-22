//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// linearForm_.cpp
//
// Code generation for function 'linearForm_'
//

// Include files
#include "linearForm_.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cstring>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace Objective {
void linearForm_(boolean_T obj_hasLinear, int obj_nvar, double workspace[11100],
                 const double H[576], const double f[75], const double x[75])
{
  int ix;
  ix = 0;
  if (obj_hasLinear) {
    if (0 <= obj_nvar - 1) {
      std::copy(&f[0], &f[obj_nvar], &workspace[0]);
    }
    ix = 1;
  }
  if (obj_nvar != 0) {
    int i;
    if ((ix != 1) && (0 <= obj_nvar - 1)) {
      std::memset(&workspace[0], 0, obj_nvar * sizeof(double));
    }
    ix = 0;
    i = obj_nvar * (obj_nvar - 1) + 1;
    for (int iac{1}; obj_nvar < 0 ? iac >= i : iac <= i; iac += obj_nvar) {
      double c;
      int i1;
      c = 0.5 * x[ix];
      i1 = (iac + obj_nvar) - 1;
      for (int ia{iac}; ia <= i1; ia++) {
        int i2;
        i2 = ia - iac;
        workspace[i2] += H[ia - 1] * c;
      }
      ix++;
    }
  }
}

} // namespace Objective
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (linearForm_.cpp)
