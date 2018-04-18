function [y] = f(x)
  y = zeros(size(x));
  for i = 1:20
    y = y + ((2 * i - 5) ./ (x - i^2)).^2;
  end
end