package TP2;

import TP4.MyInfo;

@MyInfo(annee = 2009)
public class Main {
    public void exo5() {
        // Exercice numéro 5
        Segment segment = new Segment(new Point(0, 0), new Point(4, 4));
        Cercle cercle = new Cercle(new Point(0, 0), 4);
        Point point = new Point(0, 0);
        Piletransformations piletransformations = new Piletransformations();

        piletransformations.empiler(point);

        segment.dessiner(piletransformations);
        cercle.dessiner(piletransformations);

        Point pDeplace = new Point(1, 1);
        segment.deplacer(pDeplace);
        cercle.deplacer(pDeplace);

        Image image = new Image();
        image.ajouter(segment);
        image.ajouter(cercle);

        image.dessiner(piletransformations);

        image.deplacer(pDeplace);

        image.dessiner(piletransformations);

        piletransformations.depiler();
    }

    public void exo6() {
        // Exercice numéro 6
        Segment segment = new Segment(new Point(0, 0 ), new Point(4, 4));
        Segment segment2 = new Segment(new Point(1, 1), new Point(9, 9));
        Cercle cercle = new Cercle(new Point(0, 0), 8);
        Cercle cercle2 = new Cercle(new Point(3, 3), 3);
        Point point = new Point(0, 0);
        Image image = new Image();
        Image image2 = new Image(new Point(1, 1));
        Image image3 = new Image(new Point(2, 2));
        Piletransformations pt = new Piletransformations();

        pt.empiler(point);

        image.ajouter(segment);
        image.ajouter(cercle);
        image2.ajouter(segment2);
        image2.ajouter(cercle2);

        image.dessiner(pt);
        image2.dessiner(pt);

        Point pDeplacer = new Point(2, 2);
        image2.deplacer(pDeplacer);

        image3.ajouter(image);
        image3.ajouter(image2);

        image3.dessiner(pt);

        pt.depiler();
    }

    public static void main(String[] args) {
        Main main = new Main();
        main.exo5();
        main.exo6();
    }
}