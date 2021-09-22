function [final_cost, total_cost] = ObjectiveFunction(power, load, costs, res, tariff_rate)
% Initialise the cumulative total cost variable
total_cost = zeros(1,24);

% Loop for each hour in the day
for i=1:24
    % Get the aboslute power (the negative sign is for power direction
    % so it needs to be removed)
    P = abs(power(i));
    
    % Apply power loss/efficiency curves
    P = P * 0.9;
    
    % The cost for this hour
    hour_cost = 0;
    
    if power(i) > 0 % If we are charging the BESS
        if tariff_rate > costs(i)
            % If the tariff rate is higher than the cost of buying power,
            % then sell all the RES power
            hour_cost = (P+load(i)*costs(i))-(res(i)*tariff_rate);
        else
            % The tariff rate is lower than the cost of buying power. Use
            % the RES to charge the battery
            remaining_res = res(i) - P;
            if remaining_res > 0
                % If there is excess RES remaining after charging the
                % battery
                remaining_load = load(i) - remaining_res;
                if remaining_load > 0
                    % If there is still some load remaining after putting
                    % excess RES into the load
                    hour_cost = remaining_load * costs(i);
                else
                    % If there is excess RES
                    excess_res = abs(remaining_load);
                    hour_cost = -excess_res * tariff_rate;
                end
            else
                % If there is not enough RES to charge the battery
                remaining_battery_load = abs(remaining_res);
                hour_cost = (remaining_battery_load + load(i))*costs(i);
            end
        end
    elseif power(i) == 0 % If we are neither charging nor discharging the BESS
        if tariff_rate > costs(i)
            % If the tariff rate is higher than the cost of buying power,
            % then sell all the RES power
            hour_cost = (load(i)*costs(i))-(res(i)*tariff_rate);
        else
            % The tariff rate is lower than the cost of buying power. Use
            % the RES to power the load
            remaining_load = load(i) - res(i);
            if remaining_load > 0
                % If there is still some load remaining after putting
                % RES into the load then buy energy from the grid for load
                hour_cost = remaining_load*costs(i);
            else
                % If there is excess RES then sell it to the grid
                excess_res = abs(remaining_load);
                hour_cost = -excess_res*tariff_rate;
            end
        end
    elseif power(i) < 0 % If we are discharging the BESS
        % Battery power goes towards the load
        remaining_load = load(i) - P;
        if remaining_load < 0
            % Prevent excessive discharging of the battery
            hour_cost = Inf;
        elseif remaining_load == 0
            % The battery fully powers the load so sell all RES energy
            hour_cost = -res(i) * tariff_rate;
        else
            % The battery did not fully power the load.
            if tariff_rate > costs(i)
				% If the tariff rate is higher than the cost of buying power,
				% then sell all the RES power
				hour_cost = -res(i)*tariff_rate + remaining_load*costs(i);
			else
				% The tariff rate is lower than the cost of buying power.
				% Use all RES power towards the remaining load
				remaining_load = remaining_load - res(i);
                if remaining_load > 0
					% All battery power and res power has been used. Buy
					% energy from the grid
					hour_cost = remaining_load*costs(i);
				else
					% The RES can sufficiently power the load so sell
					% excess RES energy to grid
					excess_res = abs(remaining_load);
					hour_cost = -excess_res*tariff_rate;
                end
            end
        end
    end
    
    % Cumulative sum of the total cost per hour
    if i > 1
        total_cost(i) = total_cost(i-1) + hour_cost;
    else
        total_cost(i) = hour_cost;
    end
end

% The final cost is the cumulative sum up to the last hour (24)
final_cost = total_cost(24);
end