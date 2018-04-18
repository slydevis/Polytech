package TP7;

public class Cercle {
    private Point c;
    private int r;

    public Cercle(Point p, int d) {
        c = p;
        r = d;
    }

    public void dessiner() {
        System.out.println("Cercle de rayon " + r + " et centré en " + c + ".");
    }
}
