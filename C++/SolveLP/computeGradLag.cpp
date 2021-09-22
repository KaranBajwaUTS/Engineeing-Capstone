//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// computeGradLag.cpp
//
// Code generation for function 'computeGradLag'
//

// Include files
#include "computeGradLag.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
namespace stopping {
void b_computeGradLag(double workspace[11100], int nVar, const double grad[75],
                      const double AineqTrans[3600], const double AeqTrans[75],
                      const int finiteFixed[75], int mFixed,
                      const int finiteLB[75], int mLB, const int finiteUB[75],
                      int mUB, const double lambda[148])
{
  int i;
  int ia;
  int idx;
  int ix;
  if (0 <= nVar - 1) {
    std::copy(&grad[0], &grad[nVar], &workspace[0]);
  }
  for (idx = 0; idx < mFixed; idx++) {
    i = finiteFixed[idx];
    workspace[i - 1] += lambda[idx];
  }
  for (ia = 1; ia <= nVar; ia++) {
    workspace[ia - 1] += AeqTrans[ia - 1] * lambda[mFixed];
  }
  ix = mFixed + 1;
  for (int iac{0}; iac <= 3525; iac += 75) {
    i = iac + nVar;
    for (ia = iac + 1; ia <= i; ia++) {
      idx = (ia - iac) - 1;
      workspace[idx] += AineqTrans[ia - 1] * lambda[ix];
    }
    ix++;
  }
  for (idx = 0; idx < mLB; idx++) {
    i = finiteLB[idx];
    workspace[i - 1] -= lambda[(mFixed + idx) + 49];
  }
  ix = (mFixed + mLB) + 49;
  for (idx = 0; idx < mUB; idx++) {
    i = finiteUB[idx];
    workspace[i - 1] += lambda[ix + idx];
  }
}

void computeGradLag(double workspace[75], int nVar, const double grad[75],
                    const double AineqTrans[3600], const double AeqTrans[75],
                    const int finiteFixed[75], int mFixed,
                    const int finiteLB[75], int mLB, const int finiteUB[75],
                    int mUB, const double lambda[148])
{
  int i;
  int ia;
  int idx;
  int ix;
  if (0 <= nVar - 1) {
    std::copy(&grad[0], &grad[nVar], &workspace[0]);
  }
  for (idx = 0; idx < mFixed; idx++) {
    i = finiteFixed[idx];
    workspace[i - 1] += lambda[idx];
  }
  for (ia = 1; ia <= nVar; ia++) {
    workspace[ia - 1] += AeqTrans[ia - 1] * lambda[mFixed];
  }
  ix = mFixed + 1;
  for (int iac{0}; iac <= 3525; iac += 75) {
    i = iac + nVar;
    for (ia = iac + 1; ia <= i; ia++) {
      idx = (ia - iac) - 1;
      workspace[idx] += AineqTrans[ia - 1] * lambda[ix];
    }
    ix++;
  }
  for (idx = 0; idx < mLB; idx++) {
    i = finiteLB[idx];
    workspace[i - 1] -= lambda[(mFixed + idx) + 49];
  }
  ix = (mFixed + mLB) + 49;
  for (idx = 0; idx < mUB; idx++) {
    i = finiteUB[idx];
    workspace[i - 1] += lambda[ix + idx];
  }
}

} // namespace stopping
} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (computeGradLag.cpp)
