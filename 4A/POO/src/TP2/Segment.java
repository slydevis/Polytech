package TP2;

import TP4.MyInfo;

@MyInfo(annee = 2016)
public class Segment extends Forme implements Cloneable {
    private Point end;

    public Segment(Point begin, Point end) {
        super(begin);
        this.end = end;
    }

    @Override
    public void dessiner(Piletransformations pt) {
        System.out.println("Segment :");
        System.out.println("pOrigin = " + getOrigin().additionner(pt.getCourant()));
        System.out.println("pFinal = " + end.additionner(pt.getCourant()));
    }

    @Override
    public void afficher() {
        System.out.println("Segment :");
        System.out.println("pOrigin = " + getOrigin());
        System.out.println("pFinal = " + end);
    }

    public Segment clone() throws CloneNotSupportedException {
        return (Segment) super.clone();
    }

    public static void main(String[] args) {
        System.out.println("Création d'un segment");
        Segment segment = new Segment(new Point(), new Point(1, 1));
        System.out.println("Point d'origine = " + segment.getOrigin());
        System.out.println("Point final = " + segment.end);
        segment.afficher();

        try {
            System.out.println("Copy du segment");
            Segment segmentCopy = segment.clone();
            segmentCopy.afficher();
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }

    }
}
