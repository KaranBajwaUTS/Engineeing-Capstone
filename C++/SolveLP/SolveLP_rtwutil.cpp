//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// SolveLP_rtwutil.cpp
//
// Code generation for function 'SolveLP_rtwutil'
//

// Include files
#include "SolveLP_rtwutil.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Definitions
int div_nde_s32_floor(int numerator, int denominator)
{
  int b_numerator;
  if (((numerator < 0) != (denominator < 0)) &&
      (numerator % denominator != 0)) {
    b_numerator = -1;
  } else {
    b_numerator = 0;
  }
  return numerator / denominator + b_numerator;
}

// End of code generation (SolveLP_rtwutil.cpp)
