function [battery_flow, soc, costs] = SolveLP(load_values, cost_values, res_values, tariff_rate, battery_size, battery_initial_soc, battery_minimum_soc, battery_maximum_soc, battery_max_discharge, initial_solution)
% Call fmincon to find the local minimum solution using the initial
% solution
x = fmincon(@(x) ObjectiveFunction(x, load_values, cost_values, res_values, tariff_rate), initial_solution, [], [], [], [], -battery_max_discharge*ones(1,24), battery_max_discharge*ones(1,24), @(x)ConstraintFunction(x, battery_size, battery_initial_soc, battery_minimum_soc, battery_maximum_soc), optimoptions('fmincon', 'Algorithm', 'sqp'));
% Substitute the found solution into the objective function to get the
% total costs
[~, costs] = ObjectiveFunction(x, load_values, cost_values, res_values, tariff_rate);
% Substitute the found solution into the constraints function to get the
% states of charge of the battery
[~, ~, soc] = ConstraintFunction(x, battery_size, battery_initial_soc, battery_minimum_soc, battery_maximum_soc);
% Set battery flow to found solution
battery_flow = x;
end