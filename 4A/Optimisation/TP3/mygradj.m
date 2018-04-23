function [res] = mygradj(v)
    global h N
    global L epsilon
    res = zeros(1,N) ;
    for i = 2:(N-1)
        res(i) = partialj(v,i)
    end
end
