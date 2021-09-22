//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// driver.h
//
// Code generation for function 'driver'
//

#ifndef DRIVER_H
#define DRIVER_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct g_struct_T;

struct d_struct_T;

struct l_struct_T;

struct m_struct_T;

struct h_struct_T;

struct c_struct_T;

struct i_struct_T;

struct b_struct_T;

struct j_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace fminconsqp {
void driver(const double lb[24], const double ub[24], g_struct_T *b_TrialState,
            d_struct_T *MeritFunction, const l_struct_T *FcnEvaluator,
            m_struct_T *FiniteDifferences, h_struct_T *memspace,
            c_struct_T *WorkingSet, i_struct_T *b_QRManager,
            b_struct_T *QPObjective, double Hessian[576],
            j_struct_T *b_CholManager);

}
} // namespace coder
} // namespace optim
} // namespace coder

#endif
// End of code generation (driver.h)
