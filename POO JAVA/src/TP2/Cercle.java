package TP2;

public class Cercle extends Forme {
    private int rayon;

    public Cercle(Point pOrigin, int rayon) {
        super(pOrigin);
        this.rayon = rayon;
    }

    public void dessiner(Piletransformations pt) {
        System.out.println("Cercle :");
        Point pTmp = super.getOrigin().additionner(pt.getCourant());
        System.out.println("d'origine : " + pTmp);
        System.out.println("de rayon : " + rayon);
    }

    public Point getOrigin() { return super.getOrigin(); } // For JUnit testing
}
