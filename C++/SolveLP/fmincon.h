//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// fmincon.h
//
// Code generation for function 'fmincon'
//

#ifndef FMINCON_H
#define FMINCON_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class anonymous_function;

class b_anonymous_function;

} // namespace coder

// Function Declarations
namespace coder {
void fmincon(const anonymous_function *fun, const double x0[24],
             const double lb[24], const double ub[24],
             const b_anonymous_function nonlcon, double x[24]);

}

#endif
// End of code generation (fmincon.h)
