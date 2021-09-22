//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// SolveLP.h
//
// Code generation for function 'SolveLP'
//

#ifndef SOLVELP_H
#define SOLVELP_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void SolveLP(const double load_values[24], const double cost_values[24],
                    const double res_values[24], double tariff_rate,
                    double battery_size, double battery_initial_soc,
                    double battery_minimum_soc, double battery_maximum_soc,
                    double battery_max_discharge,
                    const double initial_solution[24], double battery_flow[24],
                    double soc[25], double costs[24]);

double anon(const double load_values[24], const double cost_values[24],
            const double res_values[24], double tariff_rate,
            const double x[24]);

void anon(double battery_size, double battery_initial_soc,
          double battery_minimum_soc, double battery_maximum_soc,
          const double x[24], double varargout_1[48], double *varargout_2);

#endif
// End of code generation (SolveLP.h)
