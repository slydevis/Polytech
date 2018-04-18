package TP2;

import TP1.Entier;
import TP1.Liste;
import TP3.ExceptionFaible;
import TP3.ExceptionForte;
import TP4.MyInfo;

@MyInfo(annee = 2016)
public abstract class Structure implements Affichable, Compactable {
    public abstract void inserer(int e) throws ExceptionForte;

    public abstract void supprimer(int e) throws ExceptionFaible;

    public static void main(String[] args) {
        Structure[] structures = new Structure[10];
        structures[0] = new Entier(10);

        try {
            for (int i = 0; i < 10; ++i)
                structures[0].inserer(i);
        } catch (ExceptionForte exceptionForte) {
            exceptionForte.printStackTrace();
        }

        try {
            structures[0].supprimer(3);
        } catch (ExceptionFaible exceptionFaible) {
            exceptionFaible.printStackTrace();
        }

        structures[1] = new Liste();

        try {
            for (int i = 0; i < 9; i++)
                structures[1].inserer(i);
        } catch (ExceptionForte exceptionForte) {
            exceptionForte.printStackTrace();
        }

        try {
            structures[1].supprimer(5);
        } catch (ExceptionFaible exceptionFaible) {
            exceptionFaible.printStackTrace();
        }

        for (Structure structure : structures)
            if (structure != null)
                structure.afficher();

        // Test de l'interface Affichable
        Affichable[] affichableArray = new Affichable[2];

        Structure structuresArray = new Entier(4);

        try {
            structuresArray.inserer(1);
            structuresArray.inserer(4);
            structuresArray.inserer(3);
        } catch (ExceptionForte exceptionForte) {
            exceptionForte.printStackTrace();
        }

        Forme segment = new Segment(new Point(0, 1), new Point(3, 2));
        affichableArray[0] = structuresArray;
        affichableArray[1] = segment;

        for (Affichable aff: affichableArray) {
            if(aff != null)
                aff.afficher();
        }
    }
}
