function [factor] = gamma_(input_angle)

n = 0;

if input_angle > 360
    n = 1;
else
    if input_angle > 720
        n = 2;
    end

end

switch n
    case 1
        input_angle = input_angle - 360;
    case 2
        input_angle = input_angle - 720;
end

%
if input_angle >= 0 && input_angle < 120
    factor = 0;
end

%
if input_angle >= 120 && input_angle <= 240
    factor = input_angle/120 -1;
end

%
if input_angle > 240 && input_angle <= 360
    factor = -input_angle/120 +3;
end






end