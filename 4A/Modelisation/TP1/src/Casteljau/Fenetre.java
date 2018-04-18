package Casteljau;

import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

public class Fenetre extends JFrame {
    private int height;
    private int width;

    public Fenetre() {
        setSize(400, 400);
    }

    public Fenetre(int width, int height) {
        setSize(width, height);
        this.width = width;
        this.height = height;
    }

    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre(1280, 720);

        CasteljauPanneau panneau = new CasteljauPanneau();
        fenetre.setTitle("CastelJau");
        fenetre.add(panneau);

        panneau.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent mouseEvent) {
                super.mouseClicked(mouseEvent);
                panneau.addPoint(new Point(mouseEvent.getX(), mouseEvent.getY()));
                panneau.repaint();
            }
        });

        fenetre.setVisible(true);
        fenetre.setDefaultCloseOperation(EXIT_ON_CLOSE);

        Fenetre deboorFen = new Fenetre(1280, 720);
        deboorFen.setTitle("De Boor");
        deboorFen.setLocation(400, 0);

        DeBoorPanneau deBoorPanneau = new DeBoorPanneau();
        deboorFen.add(deBoorPanneau);

        deBoorPanneau.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent mouseEvent) {
                super.mouseClicked(mouseEvent);
                deBoorPanneau.addPoint(new Point(mouseEvent.getX(), mouseEvent.getY()));
                deBoorPanneau.repaint();
            }
        });

        deboorFen.setVisible(true);
        deboorFen.setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
}
