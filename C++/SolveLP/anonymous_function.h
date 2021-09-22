//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// anonymous_function.h
//
// Code generation for function 'anonymous_function'
//

#ifndef ANONYMOUS_FUNCTION_H
#define ANONYMOUS_FUNCTION_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct struct_T {
  double battery_size;
  double battery_initial_soc;
  double battery_minimum_soc;
  double battery_maximum_soc;
};

struct f_struct_T {
  double load_values[24];
  double cost_values[24];
  double res_values[24];
  double tariff_rate;
};

namespace coder {
class anonymous_function {
public:
  f_struct_T workspace;
};

class b_anonymous_function {
public:
  struct_T workspace;
};

} // namespace coder

#endif
// End of code generation (anonymous_function.h)
