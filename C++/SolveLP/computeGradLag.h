//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// computeGradLag.h
//
// Code generation for function 'computeGradLag'
//

#ifndef COMPUTEGRADLAG_H
#define COMPUTEGRADLAG_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
namespace stopping {
void b_computeGradLag(double workspace[11100], int nVar, const double grad[75],
                      const double AineqTrans[3600], const double AeqTrans[75],
                      const int finiteFixed[75], int mFixed,
                      const int finiteLB[75], int mLB, const int finiteUB[75],
                      int mUB, const double lambda[148]);

void computeGradLag(double workspace[75], int nVar, const double grad[75],
                    const double AineqTrans[3600], const double AeqTrans[75],
                    const int finiteFixed[75], int mFixed,
                    const int finiteLB[75], int mLB, const int finiteUB[75],
                    int mUB, const double lambda[148]);

} // namespace stopping
} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

#endif
// End of code generation (computeGradLag.h)
