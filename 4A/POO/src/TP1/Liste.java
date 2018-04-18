package TP1;

import TP2.Structure;
import TP3.NotElementListe;

/**
 * Liste Gestion de liste d'entier
 *
 * @author guillaume
 * @version 1.0
 */
public class Liste extends Structure implements Cloneable {
    private Maillon list;

    /**
     * Maillon élément entier dans la liste
     */
    private class Maillon {
        private int value;
        private Maillon next;

        /**
         * Constructeur d'un élément de liste
         *
         * @param value valeur de l'élément en entier
         * @param next  Maillon suivant
         */
        public Maillon(int value, Maillon next) {
            this.value = value;
            this.next = next;
        }

        /**
         * Affiche un maillon sur la sortie standard
         */
        private void afficher() {
            if (next != null) {
                System.out.print(value + " -> ");
                next.afficher();
            } else {
                System.out.println(value);
            }
        }
    }

    /**
     * Constructeur avec un élément dans la liste
     *
     * @param first Premier élément de la liste
     */
    public Liste(Maillon first) {
        this.list = first;
    }

    /**
     * Constructeur de liste vide
     */
    public Liste() {
        this(null);
    }

    /**
     * Vérifie si un entier est dans la liste
     *
     * @param e entier à rechercher dans la liste
     * @return true si l'entier est présent sinon false
     */
    private boolean estPresent(int e) {
        Maillon cur = list;

        while (cur != null) {
            if (cur.value == e)
                return true;
            cur = cur.next;
        }

        return false;
    }

    /**
     * Insere un nouvelle entier dans la liste si il n'est pas présent
     *
     * @param e valeur du nouvelle élément à insérer dans la liste
     */
    public void inserer(int e) {
        if (!estPresent(e))
            list = new Maillon(e, list);
    }

    /**
     * Supprime un élémént de la liste si il est présent
     *
     * @param e élément à supprimer dans la liste
     */
    public void supprimer(int e) throws NotElementListe {
        if (estPresent(e)) {
            Maillon mail = list;

            // Si la liste contiens qu'un élément
            if (mail != null && mail.next == null) {
                if (mail.value == e) {
                    list = null;
                    return;
                }
            }

            // Si l'élément est le premier élément de la liste
            if (mail != null && mail.next != null) {
                if (mail.value == e) {
                    list = mail.next;
                    return;
                }
            }

            while (mail != null) {
                if (mail.next != null && mail.next.value == e) {
                    mail.next = mail.next.next;
                    break;
                }
                mail = mail.next;
            }
        }
        else
            throw new NotElementListe(e);
    }

    @Override
    public void compacter(int n) throws NotElementListe {
        for(int i = 0; i < n; ++i)
            supprimer(list.value);
    }

    public Liste clone() throws CloneNotSupportedException {
        return (Liste) super.clone();
    }

    /**
     * Affiche la liste sur la sortie standard
     */
    public void afficher() {
        if (list == null)
            System.out.println("Liste vide");
        else
            list.afficher();
    }

    public static void main(String[] args) {
        System.out.println("======= LISTE =======");

        Liste liste = new Liste();
        liste.inserer(3);
        liste.inserer(6);
        liste.inserer(4);
        liste.inserer(3);
        liste.inserer(1);
        liste.inserer(8);
        liste.inserer(9);

        liste.afficher();

        try {
            Liste liste2 = liste.clone();
            System.out.println("======= CLONE DE LISTE ======= ");
            liste2.afficher();
            System.out.println("============================== ");

        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }

        try {
            liste.supprimer(6);
            liste.afficher();
            liste.supprimer(9);
            liste.afficher();

            liste.compacter(2);
        } catch (NotElementListe notElementListe) {
            notElementListe.printStackTrace();
        }

        liste.afficher();

        // Vidage de la liste
        System.out.println("Suppresion de tous les éléments");
        try {
            liste.supprimer(8);
            liste.supprimer(1);
            liste.supprimer(4);
            liste.supprimer(3);
        } catch (NotElementListe notElementListe) {
            notElementListe.printStackTrace();
        }
        liste.afficher();
    }
}