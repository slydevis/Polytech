clf
hold on
n = 50;
M = rand(2, n) - 0.5;
alpha = 1;
beta = 1;
epsilon = .01;
f = @(X, Y) 2*X.^2 - Y.^2;
M(1,:) = alpha * M(1,:);
M(2,:) = beta * M(2,:);x 
M(3,:) = f(M(1,:), M(2,:));
M(3,:) = M(3,:) + epsilon * rand(size(M(3,:)));
plot3(M(1,:), M(2,:), M(3,:), '.b')

# X = A\(-B)
A = [-M(1,:).',-M(2,:).',-ones(n,1)];
B = M(3,:).';
X = A\(-B);

x = -5 : 0.1 : 5;
y = x;
[XX,YY] = meshgrid(x,y);
Z = X(1)*XX+X(2)*YY+ X(3);
ZZ = f(x,YY);

mesh(XX,YY,Z);
mesh(XX,YY,ZZ);