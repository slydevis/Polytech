package TP1;

import TP2.Structure;
import TP3.HorsLimites;
import TP3.NotElementEntiers;

/**
 * Entier Permer de gérer une liste de nombre entiers distinct et ordonée
 *
 * @author guillaume
 * @version 1.0
 */
public class Entier extends Structure {
    private int data[];
    private int size = 0;
    private int nbElem = 0;

    /**
     * Construit une liste d'entrier de taille size
     *
     * @param size taille de la liste
     */
    public Entier(int size) {
        this.data = new int[size];
        this.size = size;
    }

    /**
     * Insere un nouveau entier dans la liste
     *
     * @param e élément à insérer dans la liste
     */
    public void inserer(int e) throws HorsLimites {
        if (nbElem < size) {
            int index = 0;

            // Séléction de l'index
            while (index < nbElem) {
                int elem = data[index];
                if (elem < e)
                    index++;
                else if (elem == e) // Element déjà existant on ne l'insere donc pas
                    return;
                else // Element supérieur trouvé on doit donc le mettre à l'index en cours
                    break;
            }

            // Repositionnement des éléments
            for (int i = nbElem - 1; i >= index; --i) {
                data[i + 1] = data[i];
            }

            data[index] = e;
            nbElem++;
        }
        else
            throw new HorsLimites(nbElem);
    }

    /**
     * Supprime un entier dans la liste
     *
     * @param e élément à supprimer
     */
    public void supprimer(int e) throws NotElementEntiers {
        boolean found = false;
        for (int i = 0; i < nbElem - 1; ++i) {
            if (data[i] == e)
                found = true;

            if (found)
                data[i] = data[i + 1];
        }

        if(!found)
            throw new NotElementEntiers(e);

        nbElem--;
        data[nbElem] = 0;
    }

    /**
     * Affiche la liste d'entier
     */
    public void afficher() {
        for (int e : data)
            System.out.println(e);
    }

    @Override
    public void compacter(int n) throws NotElementEntiers {
        for(int i = 0; i < n; ++i) {
            supprimer(data[0]);
        }
    }

    public static void main(String[] args) {
        System.out.println("======= ENTIER =======");

        Entier entier = new Entier(4);

        System.out.println("======= INITIALISATION =======");

        try {
            entier.inserer(4);
            entier.inserer(2);
            entier.inserer(3);
            entier.inserer(5);
            entier.inserer(2);
        } catch (HorsLimites horsLimites) {
            horsLimites.printStackTrace();
        }

        entier.afficher();

        System.out.println("======= SUPPRESION DU 3 =======");

        try {
            entier.supprimer(3);
        } catch (NotElementEntiers notElementEntiers) {
            notElementEntiers.printStackTrace();
        }

        entier.afficher();

        System.out.println("======= COMPACTER DE 2 =======");

        try {
            entier.compacter(2);
        } catch (NotElementEntiers notElementEntiers) {
            notElementEntiers.printStackTrace();
        }

        entier.afficher();

        try {
            entier.supprimer(3);
        } catch (NotElementEntiers notElementEntiers) {
            notElementEntiers.printStackTrace();
        }
    }
}
