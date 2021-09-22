//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// saveJacobian.h
//
// Code generation for function 'saveJacobian'
//

#ifndef SAVEJACOBIAN_H
#define SAVEJACOBIAN_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct g_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
namespace TrialState {
void saveJacobian(g_struct_T *obj, int nVar, const double JacCineqTrans[3600],
                  const double JacCeqTrans[75]);

}
} // namespace fminconsqp
} // namespace coder
} // namespace optim
} // namespace coder

#endif
// End of code generation (saveJacobian.h)
