package TP3;

import java.rmi.RemoteException;

public interface CalInterface {
    public Boolean estLibre(int jour) throws RemoteException;
    public Boolean libere(int jour) throws RemoteException;
    public Boolean occupe(int jour) throws RemoteException;
}
