function [ ] = plotImplicit3D( f, min, max, pas )
%PLOTIMPLICIT3D 
%   min, max : vecteurs extr�mit�s de la bo�te englobante
%   pas : vecteurs des pas de discr�tisation
%   f : fonction implicite (on trace l'isosurface f(x,y,z)=0

    step = (max - min)./pas ;
    [XX, YY, ZZ] = meshgrid(min(1):step(1):max(1), min(2):step(2):max(2), min(3):step(3):max(3)) ;
    CC = f(XX,YY,ZZ) ;
    [F, V] = MarchingCubes(XX, YY, ZZ, CC, 0)
end

