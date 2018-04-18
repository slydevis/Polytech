package TP2;

import TP4.MyInfo;

@MyInfo(annee = 2005)
public abstract class Forme implements Affichable {
    private Point pOrigin;

    public Forme() {
        this.pOrigin = new Point();
    }

    public Forme(Point pOrigin) {
        this.pOrigin = pOrigin;
    }

    public Point getOrigin() {
        return pOrigin;
    }

    public abstract void dessiner(Piletransformations piletransformations);

    public void deplacer(Point point) {
        pOrigin = pOrigin.additionner(point);
    }
}
