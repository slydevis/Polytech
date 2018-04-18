function [x,y,z] = parabolique(f, x, y, z, epsilon)
#  f[x;y] = f(x) - f(y) / (x - y)
#  f[x;y;z] = f[x;z] - f[y;z] / x - y
  while(z - x > epsilon)
    yprim = ((x + y) / 2) - ((f1(f,x,y)) / (2 * f2(f,x,y,z)));
    
    if(yprim < y)
      # Réduction à droite
      z = y;
      y = yprim;
    end
    if(yprim > y)
      # Réduction à gauche
      x = y;
      y = yprim;
    #else
      # ERREUR
      #error "ERREUR"
    end
 end
end

function [res] = f1(f, x, y)
  res = (f(x) - f(y)) / (x - y);
end

function [res] = f2(f,x, y, z)
  res = (f1(f,x,z) - f1(f,y,z)) / (x - y);
end

