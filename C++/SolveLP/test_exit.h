//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// test_exit.h
//
// Code generation for function 'test_exit'
//

#ifndef TEST_EXIT_H
#define TEST_EXIT_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct e_struct_T;

struct h_struct_T;

struct d_struct_T;

struct c_struct_T;

struct g_struct_T;

struct i_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
void test_exit(e_struct_T *Flags, h_struct_T *memspace,
               d_struct_T *MeritFunction, c_struct_T *WorkingSet,
               g_struct_T *b_TrialState, i_struct_T *b_QRManager,
               const double lb[24], const double ub[24]);

}
} // namespace coder
} // namespace optim
} // namespace coder

#endif
// End of code generation (test_exit.h)
