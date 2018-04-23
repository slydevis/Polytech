function [ res ] = partialj( v, k )
    global h N
    global L epsilon

    gvk = myg(v,k)
    gvkm1 = myg(v,k-1)
    
    tmp = 0 ;
    for i = 1:N-1
        tmp = tmp + myg(v,i)*h ;
    end
    tmp = tmp - L ;
    
    res = h/2 * (gvk + gvkm1 + 1/(h^2) * ((v(k)^2-v(k-1)^2)/gvkm1 - (v(k+1)^2-v(k)^2)/gvk)) ;
    res  = res + 2/epsilon * tmp /h * ((v(k) - v(k-1))/gvkm1 - (v(k+1)-v(k))/gvk) ;
end

