function [res] = myj(v)
    global h N
    global L epsilon
    
    res = 0 ;
    for i = 1:N-1
        res = res + myg(v,i)*h*(v(i+1)+v(i))/2 ;
    end
    
    res2 = 0 ;
    for i = 1:N-1
        res2 = res2 + myg(v,i)*h ;
    end
    res  = res + 1/epsilon * (res2-L)^2 ;
end
