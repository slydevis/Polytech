package TP2;

public class BufferCirc {
    private Object[] tampon;
    private int taille;
    private int prem, der, nbObj;

    public BufferCirc(int t) {
        taille = t;
        tampon = new Object[taille];
        prem = 0;
        der = 0;
        nbObj = 0;
    }

    public synchronized void depose(Object o) {
        tampon[der%taille] = o;
        der = (der + 1)%taille;

        if(nbObj < taille)
            nbObj++;
    }

    public synchronized Object preleve() {
        Object o = tampon[prem%taille];
        tampon[prem%taille] = null;
        prem = (prem + 1)%taille;
        der = der + (der - 1)%taille;

        if(nbObj > 0)
            nbObj--;

        return o;
    }
}
