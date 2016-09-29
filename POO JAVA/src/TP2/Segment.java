package TP2;

public class Segment extends Forme {
    private Point pFinal;

    public Segment(Point pOrigin, Point pFinal) {
        super(pOrigin);
        this.pFinal = pFinal;
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
}
