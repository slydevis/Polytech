function [Y] = descente(X, f, gf)
	diff = [1, 1];
  pas = 0.1;
  while(norm(diff) > 0.0000001)
    D = -gf(X);
    phi = @(x)f(X + x*D);
    y1 = f(X);
    y2 = f(X+pas*D);
    lmax = pas;
    while(y1 >= y2)
      y1 = y2;
      lmax += pas;
      y2 = f(X+lmax*D./norm(D));
    end
    lopt = fminbnd(phi, 0, lmax);
    diff = lopt*D;
    X += diff;
  end
  Y = X;
end