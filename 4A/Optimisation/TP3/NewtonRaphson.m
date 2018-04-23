function [res] = NewtonRaphson(f, fprime, x0, eps, itermax)
%NEWTONRAPHSON Summary of this function goes here
%   Detailed explanation goes here
    X = x0 ;
    iter = 0 ;
    diff = 1+zeros(size(X)) ;
    
    while ( (norm(diff) > eps ) && (iter<itermax) )
        diff = fprime(X) \ (-f(X))
        X = X + diff 
        iter = iter+1 ;
    end
    res = X ;
    iter
end

