function [res] = myg(v,i)
    global h N
    global L epsilon
    
    res = sqrt(1 + ((v(i+1)-v(i))/h)^2) ;
end