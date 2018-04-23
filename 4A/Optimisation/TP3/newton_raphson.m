function [ X ] = newton_raphson( f, fprime, X0, eps )
%NEWTON-RAPHSON 
%   f : R^n -> R^n
%   fprime : R^n -> matrice nxn
    
X = X0 ;
norme_ecart = 1 ;
step = 0 ;
while (norme_ecart > eps)
    A = fprime(X) ;
    % Ici : calculer diff, la solution du system A(X_k+1 - X_k) = -f(X_k)
    % On a implémenté : X contient X_k
    % et diff contiendra X_k+1 - X_k
    % %%%%
    % Donc X_k+1 s'obtient donc :
    X = X + diff 
    norme_ecart = norm(diff) ;
    step = step + 1 
end

end

