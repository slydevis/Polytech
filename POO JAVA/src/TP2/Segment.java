package TP2;

public class Segment extends Forme implements Cloneable {
    private Point pFinal;

    public Segment(Point pOrigin, Point pFinal) {
        super(pOrigin);
        this.pFinal = pFinal;
    }

    public Segment clone() throws CloneNotSupportedException {
        return (Segment) super.clone();
    }

    public void dessiner(Piletransformations pt) {
        System.out.println("Segment :");
        Point pTmp = super.getOrigin().additionner(pt.getCourant());
        System.out.println("d'origine : " + pTmp);
        pTmp = pFinal.additionner(pt.getCourant());
        System.out.println("de point final : " + pTmp);
    }

    public void deplacer(Point p) {
        pFinal = pFinal.additionner(p);
    }

    @Override
    public void afficher() {
        System.out.println("Segment ========================");
        System.out.println("Point origin = " + getOrigin());
        System.out.println("Point final = " + pFinal);
    }
}
