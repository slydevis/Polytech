package TP2;

import TP4.MyInfo;

@MyInfo(annee = 2018)
public class Piletransformations {
    private final int MAX_ITEM = 100;
    private Point[] pList;
    private int courant;

    public Piletransformations() {
        pList = new Point[MAX_ITEM];
        courant = 0;
    }

    public Point getCourant() {
        return pList[courant - 1];
    }

    public void empiler(Point p) {
        if (courant >= MAX_ITEM) {
            System.out.println("PileTransformation pleine");
            return;
        }

        if (courant > 0) {
            pList[courant] = p;
            pList[courant].additionner(pList[courant - 1]);
            courant++;
        }
        else {
            pList[courant] = p;
            courant++;
        }
    }

    public void depiler() {
        pList[courant] = null;
        courant = (courant == 0 ? 0 : courant--);
    }

    public static void main(String[] args) {
        Piletransformations piletransformations = new Piletransformations();
        Point point = new Point();
        Point point1 = new Point();
        piletransformations.empiler(point);
        piletransformations.empiler(point1);

        piletransformations.depiler();
        piletransformations.depiler();
        piletransformations.depiler();

        // Test de création d'un pile pleine
        Piletransformations pilePleine = new Piletransformations();
        for(int i = 0; i < 101; ++i)
            pilePleine.empiler(new Point(2, 2));
    }
}
