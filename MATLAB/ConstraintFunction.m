function [c, ceq, soc] = ConstraintFunction(power, battery_size, initial_soc, maximum_soc, minimum_soc)
% Battery state of charge at start of hour i
state_of_charge = zeros(1,25);
% Set the initial state of charge
state_of_charge(1) = initial_soc;
% Two constraints per hour - minimum state of charge and maximum state of
% charge
constraints = ones(1,2*24);
% Counter for constraints
counter = 1;

% Loop for each hour in the day
for i=1:24
    % State of charge at end of hour i
    state_of_charge(i+1) = state_of_charge(i) + power(i)/battery_size;
    % Minimum state of charge constraint
    constraints(counter) = state_of_charge(i+1)-minimum_soc;
    % Increment counter
    counter = counter + 1;
    % Maximum state of charge constraint
    constraints(counter) = maximum_soc-state_of_charge(i+1);
    % Increment counter
    counter = counter + 1;
end

% Set constraints
c = constraints;
% Sum of all power flow of battery must be zero to ensure the battery state
% of charge at the end of the day is equal to the state of charge at the
% start of the day.
ceq = sum(power);
soc = state_of_charge;