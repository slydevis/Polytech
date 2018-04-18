package TP2;

import TP1.Entier;
import TP3.ExceptionFaible;
import TP3.HorsLimites;
import TP3.NotElementEntiers;
import TP4.MyInfo;

@MyInfo(annee = 2016)
public interface Compactable {
    public void compacter(int n) throws ExceptionFaible;

    public static void main(String[] args) {
        Compactable[] compactables = new Compactable[2];

        Entier structures = new Entier(4);
        try {
            structures.inserer(1);
            structures.inserer(2);
            structures.inserer(3);
            structures.inserer(4);
        } catch (HorsLimites horsLimites) {
            horsLimites.printStackTrace();
        }

        Image images = new Image();
        images.ajouter(new Cercle(new Point(0, 0), 3));
        images.ajouter(new Cercle(new Point(0, 1), 3));
        images.ajouter(new Cercle(new Point(0, 2), 3));
        images.ajouter(new Cercle(new Point(0, 3), 3));

        compactables[0] = images;
        compactables[1] = structures;

        try {
            for (Compactable comp : compactables) {
                if (comp != null)
                    comp.compacter(3);
            }
        } catch (ExceptionFaible exceptionFaible) {
            exceptionFaible.printStackTrace();
        }

        images.afficher();
        structures.afficher();
    }
}
