function [r] = ff2(x, y)
  global a b
  r = ff1(x,y) .* (2 + sin(x.^2 + y^2));
end