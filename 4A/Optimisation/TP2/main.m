global a b;
a = 1;
b = 2;

X = -5 : 1 : 5;
Y = X;
[XX, YY] = meshgrid(X,Y);
Z = ff1(XX, YY);
surf(XX,YY,Z);

M = descente([-1; 1], @(x)ff3(X), @(x)gradf1(x))