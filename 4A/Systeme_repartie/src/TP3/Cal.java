package TP3;

import java.rmi.RemoteException;

public class Cal implements CalInterface {
    private String nom;

    public Cal(String nom) {
        this.nom = nom;
    }

    @Override
    public Boolean estLibre(int jour) throws RemoteException {
        return null;
    }

    @Override
    public Boolean libere(int jour) throws RemoteException {
        return null;
    }

    @Override
    public Boolean occupe(int jour) throws RemoteException {
        return null;
    }
}
