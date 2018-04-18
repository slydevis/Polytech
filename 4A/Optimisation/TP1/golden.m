function [a, b] = golden(fx, a, b, epsilon)
  tho = (1 + sqrt(5)) / 2;
 
  while(b - a > epsilon)
    aprime = a + (b - a) / (tho^2);
    bprime = a + (b - a)/ tho;
    
    fa = fx(aprime);
    fb = fx(bprime);
    
    if(fa < fb)
      b = bprime;
    end
    if(fa > fb)
      a = aprime;
    end
    if(fa == fb)
      # ERREUR
      error "ERREUR"
    end
  end
end
