//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// driver1.h
//
// Code generation for function 'driver1'
//

#ifndef DRIVER1_H
#define DRIVER1_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct g_struct_T;

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
namespace qpactiveset {
void driver(const double H[576], const double f[75], g_struct_T *solution,
            h_struct_T *memspace, c_struct_T *workingset, i_struct_T *qrmanager,
            j_struct_T *cholmanager, b_struct_T *objective, k_struct_T *options,
            k_struct_T *runTimeOptions);

}
} // namespace coder
} // namespace optim
} // namespace coder

#endif
// End of code generation (driver1.h)
