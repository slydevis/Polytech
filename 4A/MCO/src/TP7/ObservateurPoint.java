package TP7;

import java.util.Observable;
import java.util.Observer;

public class ObservateurPoint implements Observer {

    private Point copie;

    public ObservateurPoint(Point p) {
        copie = p;
    }

    @Override
    public void update(Observable observable, Object o) {
        Point p = (Point) observable;
        System.out.println(p.x);
        System.out.println(p.y);
        copie.modifier(p.x, p.y);
    }

    public static void main(String[] args) {
        Point p1 = new Point(0, 0);
        Point p1_bis = p1.clone();

        ObservateurPoint obs = new ObservateurPoint(p1_bis);

        p1.addObserver(obs);

        Cercle c = new Cercle(p1_bis, 3);
        c.dessiner();

        p1.modifier(2, 3);
        System.out.println("On a modifier le point observé par le centre : " + p1);
        c.dessiner();
    }
}
