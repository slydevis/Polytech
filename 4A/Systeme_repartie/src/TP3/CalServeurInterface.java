package TP3;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface CalServeurInterface extends Remote {
    public CalInterface createCal(String nom) throws RemoteException;
    public Boolean intersectionLibre(String[] noms, int jour) throws RemoteException;
    public void reserve(String[] noms, int jour) throws RemoteException, ReservImpossible;
}
