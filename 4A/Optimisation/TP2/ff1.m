function [r] = ff1(x, y)
  global a b
  r = (a*(x.^2)) + (b*(y.^2));
end