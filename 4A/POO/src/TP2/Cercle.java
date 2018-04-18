package TP2;

import TP4.MyInfo;

@MyInfo(annee = 2016)
public class Cercle extends Forme {
    private int rayon;

    public Cercle(Point origin, int rayon) {
        super(origin);
        this.rayon = rayon;
    }

    public void dessiner(Piletransformations pt) {
        System.out.println("Cercle :");
        System.out.println("pOrigin : " + getOrigin().additionner(pt.getCourant()));
        System.out.println("Rayon : " + rayon);
    }

    @Override
    public void afficher() {
        System.out.println("Cercle :");
        System.out.println("pOrigin : " + getOrigin());
        System.out.println("Rayon : " + rayon);
    }

    public static void main(String[] args) {
        Cercle cercle = new Cercle(new Point(), 3);
        Piletransformations pt = new Piletransformations();
        pt.empiler(new Point(2, 2));
        cercle.deplacer(new Point(3, 3));
        cercle.dessiner(pt);
        cercle.afficher();
    }
}
