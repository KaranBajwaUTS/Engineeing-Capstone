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

#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

static void main_SolveLP()
{
  static struct Battery {
    double size, initial_soc, maximum_soc, minimum_soc, maximum_discharge;
  } battery;

  using namespace std;
  ifstream ifs("capstone.json");
  json capstone_data = json::parse(ifs);

  vector<double> loads = capstone_data["loads"].get<vector<double>>();
  vector<double> power_costs = capstone_data["costs"].get<vector<double>>();
  vector<double> res = capstone_data["res"].get<vector<double>>();

  double tariff_rate = capstone_data["tariff_rate"].get<double>();

  vector<double> initial_solution =
      capstone_data["initial_solution"].get<vector<double>>();

  battery.size = capstone_data["battery"]["size"].get<double>();
  battery.initial_soc = capstone_data["battery"]["initial_soc"].get<double>();
  battery.maximum_soc = capstone_data["battery"]["maximum_soc"].get<double>();
  battery.minimum_soc = capstone_data["battery"]["minimum_soc"].get<double>();
  battery.maximum_discharge =
      capstone_data["battery"]["maximum_discharge"].get<double>();

  double soc[25];
  double battery_flow[24];
  double costs[24];

  SolveLP(loads.data(), power_costs.data(), res.data(), tariff_rate,
          battery.size, battery.initial_soc, battery.minimum_soc,
          battery.maximum_soc, battery.maximum_discharge,
          initial_solution.data(), battery_flow, soc, costs);

  json output;
  output["costs"] = vector<double>(costs, costs + 24);
  output["soc"] = vector<double>(soc, soc + 25);
  output["battery_power"] = vector<double>(battery_flow, battery_flow + 24);
  std::ofstream o("output.json");
  o << output << std::endl;
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
