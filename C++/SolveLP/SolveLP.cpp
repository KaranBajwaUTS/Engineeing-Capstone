//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// SolveLP.cpp
//
// Code generation for function 'SolveLP'
//

// Include files
#include "SolveLP.h"
#include "anonymous_function.h"
#include "fmincon.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <string.h>

// Function Definitions
void SolveLP(const double load_values[24], const double cost_values[24],
             const double res_values[24], double tariff_rate,
             double battery_size, double battery_initial_soc,
             double battery_minimum_soc, double battery_maximum_soc,
             double battery_max_discharge, const double initial_solution[24],
             double battery_flow[24], double soc[25], double costs[24])
{
  coder::anonymous_function b_this;
  coder::b_anonymous_function c_this;
  double b_battery_max_discharge[24];
  double c_battery_max_discharge[24];
  int i;
  //  Call fmincon to find the local minimum solution
  b_this.workspace.tariff_rate = tariff_rate;
  c_this.workspace.battery_size = battery_size;
  c_this.workspace.battery_initial_soc = battery_initial_soc;
  c_this.workspace.battery_minimum_soc = battery_minimum_soc;
  c_this.workspace.battery_maximum_soc = battery_maximum_soc;
  for (i = 0; i < 24; i++) {
    b_this.workspace.load_values[i] = load_values[i];
    b_this.workspace.cost_values[i] = cost_values[i];
    b_this.workspace.res_values[i] = res_values[i];
    b_battery_max_discharge[i] = -battery_max_discharge;
    c_battery_max_discharge[i] = battery_max_discharge;
  }
  coder::fmincon(&b_this, initial_solution, b_battery_max_discharge,
                 c_battery_max_discharge, c_this, battery_flow);
  //  Substitute the found solution into the objective function to get the
  //  total costs
  //  Initialise the cumulative total cost variable
  //  Loop for each hour in the day
  for (i = 0; i < 24; i++) {
    double P;
    double hour_cost;
    double remaining_load;
    costs[i] = 0.0;
    //  Get the aboslute power (the negative sign is for power direction
    //  so it needs to be removed)
    //  Apply power loss/efficiency curves
    remaining_load = battery_flow[i];
    P = std::abs(remaining_load) * 0.9;
    //  The cost for this hour
    hour_cost = 0.0;
    if (remaining_load > 0.0) {
      //  If we are charging the BESS
      if (tariff_rate > cost_values[i]) {
        //  If the tariff rate is higher than the cost of buying power,
        //  then sell all the RES power
        hour_cost =
            (P + load_values[i] * cost_values[i]) - res_values[i] * tariff_rate;
      } else {
        //  The tariff rate is lower than the cost of buying power. Use
        //  the RES to charge the battery
        remaining_load = res_values[i] - P;
        if (remaining_load > 0.0) {
          //  If there is excess RES remaining after charging the
          //  battery
          remaining_load = load_values[i] - remaining_load;
          if (remaining_load > 0.0) {
            //  If there is still some load remaining after putting
            //  excess RES into the load
            hour_cost = remaining_load * cost_values[i];
          } else {
            //  If there is excess RES
            hour_cost = -std::abs(remaining_load) * tariff_rate;
          }
        } else {
          //  If there is not enough RES to charge the battery
          hour_cost =
              (std::abs(remaining_load) + load_values[i]) * cost_values[i];
        }
      }
    } else if (remaining_load == 0.0) {
      //  If we are neither charging nor discharging the BESS
      if (tariff_rate > cost_values[i]) {
        //  If the tariff rate is higher than the cost of buying power,
        //  then sell all the RES power
        hour_cost =
            load_values[i] * cost_values[i] - res_values[i] * tariff_rate;
      } else {
        //  The tariff rate is lower than the cost of buying power. Use
        //  the RES to power the load
        remaining_load = load_values[i] - res_values[i];
        if (remaining_load > 0.0) {
          //  If there is still some load remaining after putting
          //  excess RES into the load
          hour_cost = remaining_load * cost_values[i];
        } else {
          //  If there is excess RES
          hour_cost = -std::abs(remaining_load) * tariff_rate;
        }
      }
    } else if (remaining_load < 0.0) {
      //  If we are discharging the BESS
      remaining_load = load_values[i] - P;
      if (remaining_load < 0.0) {
        //  Prevent excessive discharging of the battery
        hour_cost = rtInf;
      } else if (remaining_load == 0.0) {
        //  The battery full powers the load so sell all RES energy
        hour_cost = -res_values[i] * tariff_rate;

        //  The battery did not fully power the load.
      } else if (tariff_rate > cost_values[i]) {
        //  If the tariff rate is higher than the cost of buying power,
        //  then sell all the RES power
        hour_cost =
            -res_values[i] * tariff_rate + remaining_load * cost_values[i];
      } else {
        //  The tariff rate is lower than the cost of buying power.
        //  Use all RES power towards the remaining load
        remaining_load -= res_values[i];
        if (remaining_load > 0.0) {
          //  All battery power and res power has been used. Buy
          //  energy from the grid
          hour_cost = remaining_load * cost_values[i];
        } else {
          //  The RES can sufficiently power the load
          hour_cost = -std::abs(remaining_load) * tariff_rate;
        }
      }
    }
    if (i + 1 > 1) {
      costs[i] = costs[i - 1] + hour_cost;
    } else {
      costs[0] = hour_cost;
    }
  }
  //  Substitute the found solution into the constraints function to get the
  //  states of charge of the battery
  //  Battery state of charge at start of hour i
  std::memset(&soc[0], 0, 25U * sizeof(double));
  //  Set the initial state of charge
  soc[0] = battery_initial_soc;
  //  Two constraints per hours - minimum state of charge and maximum state of
  //  charge
  //  Counter for constraints
  //  Loop for each hour in the day
  for (i = 0; i < 24; i++) {
    //  Battery power at hour i
    //  State of charge at end of hour i
    soc[i + 1] = soc[i] + battery_flow[i] / battery_size;
    //  Minimum state of charge constraint
    //  Increment counter
    //  Maximum state of charge constraint
    //  Increment counter
  }
  //  Set constraints
  //  Sum of all power flow of battery must be zero to ensure the battery state
  //  of charge at the end of the day is equal to the state of charge at the
  //  start of the day.
  //  Set battery flow to found solution
}

double anon(const double load_values[24], const double cost_values[24],
            const double res_values[24], double tariff_rate, const double x[24])
{
  double total_cost[24];
  //  Initialise the cumulative total cost variable
  //  Loop for each hour in the day
  for (int i{0}; i < 24; i++) {
    double P;
    double hour_cost;
    double remaining_load;
    total_cost[i] = 0.0;
    //  Get the aboslute power (the negative sign is for power direction
    //  so it needs to be removed)
    //  Apply power loss/efficiency curves
    remaining_load = x[i];
    P = std::abs(remaining_load) * 0.9;
    //  The cost for this hour
    hour_cost = 0.0;
    if (remaining_load > 0.0) {
      //  If we are charging the BESS
      if (tariff_rate > cost_values[i]) {
        //  If the tariff rate is higher than the cost of buying power,
        //  then sell all the RES power
        hour_cost =
            (P + load_values[i] * cost_values[i]) - res_values[i] * tariff_rate;
      } else {
        //  The tariff rate is lower than the cost of buying power. Use
        //  the RES to charge the battery
        remaining_load = res_values[i] - P;
        if (remaining_load > 0.0) {
          //  If there is excess RES remaining after charging the
          //  battery
          remaining_load = load_values[i] - remaining_load;
          if (remaining_load > 0.0) {
            //  If there is still some load remaining after putting
            //  excess RES into the load
            hour_cost = remaining_load * cost_values[i];
          } else {
            //  If there is excess RES
            hour_cost = -std::abs(remaining_load) * tariff_rate;
          }
        } else {
          //  If there is not enough RES to charge the battery
          hour_cost =
              (std::abs(remaining_load) + load_values[i]) * cost_values[i];
        }
      }
    } else if (remaining_load == 0.0) {
      //  If we are neither charging nor discharging the BESS
      if (tariff_rate > cost_values[i]) {
        //  If the tariff rate is higher than the cost of buying power,
        //  then sell all the RES power
        hour_cost =
            load_values[i] * cost_values[i] - res_values[i] * tariff_rate;
      } else {
        //  The tariff rate is lower than the cost of buying power. Use
        //  the RES to power the load
        remaining_load = load_values[i] - res_values[i];
        if (remaining_load > 0.0) {
          //  If there is still some load remaining after putting
          //  excess RES into the load
          hour_cost = remaining_load * cost_values[i];
        } else {
          //  If there is excess RES
          hour_cost = -std::abs(remaining_load) * tariff_rate;
        }
      }
    } else if (remaining_load < 0.0) {
      //  If we are discharging the BESS
      remaining_load = load_values[i] - P;
      if (remaining_load < 0.0) {
        //  Prevent excessive discharging of the battery
        hour_cost = rtInf;
      } else if (remaining_load == 0.0) {
        //  The battery full powers the load so sell all RES energy
        hour_cost = -res_values[i] * tariff_rate;

        //  The battery did not fully power the load.
      } else if (tariff_rate > cost_values[i]) {
        //  If the tariff rate is higher than the cost of buying power,
        //  then sell all the RES power
        hour_cost =
            -res_values[i] * tariff_rate + remaining_load * cost_values[i];
      } else {
        //  The tariff rate is lower than the cost of buying power.
        //  Use all RES power towards the remaining load
        remaining_load -= res_values[i];
        if (remaining_load > 0.0) {
          //  All battery power and res power has been used. Buy
          //  energy from the grid
          hour_cost = remaining_load * cost_values[i];
        } else {
          //  The RES can sufficiently power the load
          hour_cost = -std::abs(remaining_load) * tariff_rate;
        }
      }
    }
    if (i + 1 > 1) {
      total_cost[i] = total_cost[i - 1] + hour_cost;
    } else {
      total_cost[0] = hour_cost;
    }
  }
  return total_cost[23];
}

void anon(double battery_size, double battery_initial_soc,
          double battery_minimum_soc, double battery_maximum_soc,
          const double x[24], double varargout_1[48], double *varargout_2)
{
  double state_of_charge[25];
  int i;
  //  Battery state of charge at start of hour i
  std::memset(&state_of_charge[0], 0, 25U * sizeof(double));
  //  Set the initial state of charge
  state_of_charge[0] = battery_initial_soc;
  //  Two constraints per hours - minimum state of charge and maximum state of
  //  charge
  for (i = 0; i < 48; i++) {
    varargout_1[i] = 1.0;
  }
  //  Counter for constraints
  //  Loop for each hour in the day
  for (i = 0; i < 24; i++) {
    double d;
    int varargout_1_tmp;
    //  Battery power at hour i
    //  State of charge at end of hour i
    d = state_of_charge[i] + x[i] / battery_size;
    state_of_charge[i + 1] = d;
    //  Minimum state of charge constraint
    varargout_1_tmp = i << 1;
    varargout_1[varargout_1_tmp] = d - battery_maximum_soc;
    //  Increment counter
    //  Maximum state of charge constraint
    varargout_1[varargout_1_tmp + 1] = battery_minimum_soc - d;
    //  Increment counter
  }
  //  Set constraints
  //  Sum of all power flow of battery must be zero to ensure the battery state
  //  of charge at the end of the day is equal to the state of charge at the
  //  start of the day.
  *varargout_2 = x[0];
  for (i = 0; i < 23; i++) {
    *varargout_2 += x[i + 1];
  }
}

// End of code generation (SolveLP.cpp)
