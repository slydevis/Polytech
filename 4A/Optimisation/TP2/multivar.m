# Variable global : global a b c
# definition d'une variable global : a = 3
# En debut de la fonction (a l'interieur) : global a b

global a b
a = 1;
b = 2;

hold on;

X = -1 : 0.1 : 1;
Y = X;
[XX, YY] = meshgrid(X, Y);
ZZ = ff2(XX,YY);
# mesh(XX,YY, ZZ);
 surf(XX, YY, ZZ);
 
#[x] = gradient(@(x)f(x), 4, 0.001)

#[a, b] = fminbnd(@(x)f(x),1,4)