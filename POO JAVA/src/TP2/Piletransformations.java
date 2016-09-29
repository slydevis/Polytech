package TP2;

public class Piletransformations {
    private final int MAX_ITEMS = 100;
    private Point[] pList;
    private int courant = 0;

    public Piletransformations() {
        pList = new Point[MAX_ITEMS];
    }

    public Point getCourant() {
        return pList[courant];
    }

    public void depiler() {
        pList[courant] = null;
        courant = (courant == 0 ? 0 : courant--);
    }

    public void empiler(Point p) {
        if(courant + 1 >= MAX_ITEMS) {
            System.out.println("Pile pleine");
            return;
        }

        courant++;
        pList[courant] = p;
    }
}
