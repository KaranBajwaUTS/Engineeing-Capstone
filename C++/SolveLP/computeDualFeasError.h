//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// computeDualFeasError.h
//
// Code generation for function 'computeDualFeasError'
//

#ifndef COMPUTEDUALFEASERROR_H
#define COMPUTEDUALFEASERROR_H

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
void computeDualFeasError(int nVar, const double gradLag[75], boolean_T *gradOK,
                          double *val);

}
} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

#endif
// End of code generation (computeDualFeasError.h)
