//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_SolveLP_api.h
//
// Code generation for function 'SolveLP'
//

#ifndef _CODER_SOLVELP_API_H
#define _CODER_SOLVELP_API_H

// Include files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void SolveLP(real_T load_values[24], real_T cost_values[24],
             real_T res_values[24], real_T tariff_rate, real_T battery_size,
             real_T battery_initial_soc, real_T battery_minimum_soc,
             real_T battery_maximum_soc, real_T battery_max_discharge,
             real_T initial_solution[24], real_T battery_flow[24],
             real_T soc[25], real_T costs[24]);

void SolveLP_api(const mxArray *const prhs[10], int32_T nlhs,
                 const mxArray *plhs[3]);

void SolveLP_atexit();

void SolveLP_initialize();

void SolveLP_terminate();

void SolveLP_xil_shutdown();

void SolveLP_xil_terminate();

#endif
// End of code generation (_coder_SolveLP_api.h)
