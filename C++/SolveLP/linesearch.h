//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// linesearch.h
//
// Code generation for function 'linesearch'
//

#ifndef LINESEARCH_H
#define LINESEARCH_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct g_struct_T;

namespace coder {
class anonymous_function;

class b_anonymous_function;

} // namespace coder

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
void linesearch(boolean_T *evalWellDefined, int WorkingSet_nVar,
                g_struct_T *b_TrialState, double MeritFunction_penaltyParam,
                double MeritFunction_phi, double MeritFunction_phiPrimePlus,
                double MeritFunction_phiFullStep,
                const anonymous_function *FcnEvaluator_objfun,
                const b_anonymous_function FcnEvaluator_nonlcon,
                boolean_T socTaken, double *alpha, int *exitflag);

}
} // namespace coder
} // namespace optim
} // namespace coder

#endif
// End of code generation (linesearch.h)
