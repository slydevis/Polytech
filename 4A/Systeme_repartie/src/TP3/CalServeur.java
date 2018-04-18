package TP3;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;

public class CalServeur extends UnicastRemoteObject implements CalServeurInterface {
    HashMap<String, Cal> lesCals;

    public CalServeur() throws RemoteException {
        super();
        lesCals = new HashMap<String, Cal>();
    }

    @Override
    public CalInterface createCal(String nom) throws RemoteException {
        Cal unCal = new Cal(nom);
        lesCals.put(nom, unCal);
        return unCal;
    }

    @Override
    public Boolean intersectionLibre(String[] noms, int jour) throws RemoteException {
        boolean res = true;

        for(int i = 0; i < noms.length; ++i){
            res &= lesCals.get(noms[i]).estLibre(jour);
        }
x
        return new Boolean(res);
    }

    @Override
    public void reserve(String[] noms, int jour) throws RemoteException, ReservImpossible {
        if(intersectionLibre(noms, jour)) {
            for(int i = 0; i < noms.length; ++i) {
                lesCals.get(noms[i]).occupe(jour);
            }
        }
        else
            throw new ReservImpossible();
    }
}
