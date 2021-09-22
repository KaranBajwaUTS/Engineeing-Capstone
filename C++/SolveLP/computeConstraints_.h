//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// computeConstraints_.h
//
// Code generation for function 'computeConstraints_'
//

#ifndef COMPUTECONSTRAINTS__H
#define COMPUTECONSTRAINTS__H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
namespace coder {
class b_anonymous_function;

}

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace utils {
namespace ObjNonlinEvaluator {
int computeConstraints_(const b_anonymous_function obj_nonlcon,
                        const double x[24], double Cineq_workspace[48],
                        double *Ceq_workspace);

}
} // namespace utils
} // namespace coder
} // namespace optim
} // namespace coder

#endif
// End of code generation (computeConstraints_.h)
