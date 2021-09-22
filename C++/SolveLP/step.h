//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// step.h
//
// Code generation for function 'step'
//

#ifndef STEP_H
#define STEP_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct g_struct_T;

struct d_struct_T;

struct h_struct_T;

struct c_struct_T;

struct i_struct_T;

struct j_struct_T;

struct b_struct_T;

struct k_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
boolean_T b_step(int *STEP_TYPE, double Hessian[576], const double lb[24],
                 const double ub[24], g_struct_T *b_TrialState,
                 d_struct_T *MeritFunction, h_struct_T *memspace,
                 c_struct_T *WorkingSet, i_struct_T *b_QRManager,
                 j_struct_T *b_CholManager, b_struct_T *QPObjective,
                 k_struct_T *qpoptions);

}
} // namespace coder
} // namespace optim
} // namespace coder

#endif
// End of code generation (step.h)
