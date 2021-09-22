//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// computeComplError.cpp
//
// Code generation for function 'computeComplError'
//

// Include files
#include "computeComplError.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <string.h>

// Function Definitions
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
namespace stopping {
double computeComplError(const double xCurrent[24], const double cIneq[48],
                         const int finiteLB[75], int mLB, const double lb[24],
                         const int finiteUB[75], int mUB, const double ub[24],
                         const double lambda[148], int iL0)
{
  double lbDelta;
  double lbLambda;
  double nlpComplError;
  int i;
  int idx;
  int ubOffset;
  nlpComplError = 0.0;
  for (idx = 0; idx < 48; idx++) {
    lbDelta = lambda[(iL0 + idx) - 1];
    lbLambda = cIneq[idx];
    nlpComplError = std::fmax(
        nlpComplError, std::fmin(std::abs(lbLambda * lbDelta),
                                 std::fmin(std::abs(lbLambda), lbDelta)));
  }
  ubOffset = (iL0 + mLB) + 47;
  for (idx = 0; idx < mLB; idx++) {
    i = finiteLB[idx];
    lbDelta = xCurrent[i - 1] - lb[i - 1];
    lbLambda = lambda[(iL0 + idx) + 47];
    nlpComplError = std::fmax(
        nlpComplError, std::fmin(std::abs(lbDelta * lbLambda),
                                 std::fmin(std::abs(lbDelta), lbLambda)));
  }
  for (idx = 0; idx < mUB; idx++) {
    i = finiteUB[idx];
    lbDelta = ub[i - 1] - xCurrent[i - 1];
    lbLambda = lambda[ubOffset + idx];
    nlpComplError = std::fmax(
        nlpComplError, std::fmin(std::abs(lbDelta * lbLambda),
                                 std::fmin(std::abs(lbDelta), lbLambda)));
  }
  return nlpComplError;
}

} // namespace stopping
} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

// End of code generation (computeComplError.cpp)
