//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// main.cpp
//
// Code generation for function 'main'
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include files
#include "main.h"
#include "SolveLP.h"
#include "SolveLP_terminate.h"
#include "rt_nonfinite.h"
#include <string.h>

// Function Declarations
static void argInit_1x24_real_T(double result[24]);

static double argInit_real_T();

static void main_SolveLP();

// Function Definitions
static void argInit_1x24_real_T(double result[24])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 24; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real_T();
  }
}

static double argInit_real_T()
{
  return 0.0;
}

static void main_SolveLP()
{
  double soc[25];
  double battery_flow[24];
  double costs[24];
  double load_values_tmp[24];
  double tariff_rate_tmp;
  // Initialize function 'SolveLP' input arguments.
  // Initialize function input argument 'load_values'.
  argInit_1x24_real_T(load_values_tmp);
  // Initialize function input argument 'cost_values'.
  // Initialize function input argument 'res_values'.
  tariff_rate_tmp = argInit_real_T();
  // Initialize function input argument 'initial_solution'.
  // Call the entry-point 'SolveLP'.
  SolveLP(load_values_tmp, load_values_tmp, load_values_tmp, tariff_rate_tmp,
          tariff_rate_tmp, tariff_rate_tmp, tariff_rate_tmp, tariff_rate_tmp,
          tariff_rate_tmp, load_values_tmp, battery_flow, soc, costs);
}

int main(int, char **)
{
  // The initialize function is being called automatically from your entry-point
  // function. So, a call to initialize is not included here. Invoke the
  // entry-point functions.
  // You can call entry-point functions multiple times.
  main_SolveLP();
  // Terminate the application.
  // You do not need to do this more than one time.
  SolveLP_terminate();
  return 0;
}

// End of code generation (main.cpp)
