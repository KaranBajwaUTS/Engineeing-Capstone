//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// BFGSUpdate.cpp
//
// Code generation for function 'BFGSUpdate'
//

// Include files
#include "BFGSUpdate.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
boolean_T BFGSUpdate(int nvar, double Bk[576], const double sk[75],
                     double yk[75], double workspace[11100])
{
  double curvatureS;
  double dotSY;
  double theta;
  int i;
  int i1;
  int iac;
  int ix;
  int k;
  boolean_T success;
  dotSY = 0.0;
  for (k = 0; k < nvar; k++) {
    dotSY += sk[k] * yk[k];
    workspace[k] = 0.0;
  }
  ix = 0;
  i = 24 * (nvar - 1) + 1;
  for (iac = 1; iac <= i; iac += 24) {
    i1 = (iac + nvar) - 1;
    for (int ia{iac}; ia <= i1; ia++) {
      k = ia - iac;
      workspace[k] += Bk[ia - 1] * sk[ix];
    }
    ix++;
  }
  curvatureS = 0.0;
  if (nvar >= 1) {
    for (k = 0; k < nvar; k++) {
      curvatureS += sk[k] * workspace[k];
    }
  }
  if (dotSY < 0.2 * curvatureS) {
    theta = 0.8 * curvatureS / (curvatureS - dotSY);
    for (k = 0; k < nvar; k++) {
      yk[k] *= theta;
    }
    if (!(1.0 - theta == 0.0)) {
      ix = nvar - 1;
      for (k = 0; k <= ix; k++) {
        yk[k] += (1.0 - theta) * workspace[k];
      }
    }
    dotSY = 0.0;
    for (k = 0; k < nvar; k++) {
      dotSY += sk[k] * yk[k];
    }
  }
  if ((curvatureS > 2.2204460492503131E-16) &&
      (dotSY > 2.2204460492503131E-16)) {
    success = true;
  } else {
    success = false;
  }
  if (success) {
    theta = -1.0 / curvatureS;
    if (!(theta == 0.0)) {
      ix = 0;
      for (k = 0; k < nvar; k++) {
        if (workspace[k] != 0.0) {
          curvatureS = workspace[k] * theta;
          i = ix + 1;
          i1 = nvar + ix;
          for (iac = i; iac <= i1; iac++) {
            Bk[iac - 1] += workspace[(iac - ix) - 1] * curvatureS;
          }
        }
        ix += 24;
      }
    }
    theta = 1.0 / dotSY;
    if (!(theta == 0.0)) {
      ix = 0;
      for (k = 0; k < nvar; k++) {
        if (yk[k] != 0.0) {
          curvatureS = yk[k] * theta;
          i = ix + 1;
          i1 = nvar + ix;
          for (iac = i; iac <= i1; iac++) {
            Bk[iac - 1] += yk[(iac - ix) - 1] * curvatureS;
          }
        }
        ix += 24;
      }
    }
  }
  return success;
}

} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (BFGSUpdate.cpp)
