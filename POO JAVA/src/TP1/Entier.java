package TP1;

import java.util.Arrays;

import TP2.Structure;
import TP3.NotElementEntiers;

public class Entier extends Structure {
    private int[] data;
    private int maxElements;
    private int nbElements = 0;

    /**
     * @param taille nombre d'entier maximum stocké
     */
    public Entier(int taille) {
        maxElements = taille;
        data = new int[maxElements];
    }

    /**
     * @param entier à insérer dans l'ensemble d'entier
     */
    public void inserer(int entier) {
        assert nbElements < maxElements;

        if(Arrays.binarySearch(data, entier) < 0) {
            data[nbElements] = entier;
            nbElements++;
            Arrays.sort(data, 0, nbElements);
        }
    }

    /**
     * @param entier à supprimer si il existe
     */
    public void supprimer(int entier) {
        try {
            int index = Arrays.binarySearch(data, entier);
            if(index < 0)
                throw new NotElementEntiers(entier);

            for(int i = index; i < maxElements - 1; ++i)
                data[i] = data[i + 1];
            nbElements--;
        } catch (NotElementEntiers notElementEntiers) {
            notElementEntiers.printStackTrace();
        }
    }

    @Override
    public void afficher() {
        System.out.println(Arrays.toString(data));
    }

    @Override
    public void compacter(int nb) {
        for(int i = 0; i < nb; ++i)
            supprimer(i);
    }

    public static void main(String[] args) {
        Entier entier = new Entier(6);
        entier.inserer(1);
        entier.afficher();

        entier.inserer(6);
        entier.inserer(3);
        entier.inserer(3);
        entier.inserer(2);
        entier.afficher();

        entier.supprimer(2);
        entier.afficher();
        entier.supprimer(3);
        entier.afficher();
    }
}