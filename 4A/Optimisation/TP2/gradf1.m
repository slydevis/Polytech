function [Y] = gradf1(X)
  global a b;
	Y = [2*a*X(1)+b*X(2).^2; a*X(1)+2*b*X(2)];
end