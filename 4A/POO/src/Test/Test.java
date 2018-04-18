package Test;

import TP1.*;
import TP2.*;

/**
 * Test Réalise des test sur les classes afin de pouvoir
 * avoir la couverture (pour covertura)
 */
public class Test {
    public static void main(String[] args) {
        // TP1
        Pile.main(args);
        Entier.main(args);
        Liste.main(args);
        ArbreBinaire.main(args);
        // TP2
        Point.main(args);
        Segment.main(args);
        Cercle.main(args);
        Piletransformations.main(args);
        Image.main(args);
        Main.main(args);
        Structure.main(args);
        Compactable.main(args);
    }
}
