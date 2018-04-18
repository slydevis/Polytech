# f = @(x) x^2 => x -> x^2

#hold on
#X = 0:0.1:10;
#ff = @(x) f(x);
#Y = ff(X);
#plot(X, Y);

[a, b] = golden(@(x)f(x), 1, 4, 0.001)
[a, b] = fminbnd(@(x)f(x),1,4)

[x, y, z] = parabolique(@(x)f(x), 1.1, 2, 3.9, 0.001)

[x] = newton(@(x)f(x), 4, 0.001)