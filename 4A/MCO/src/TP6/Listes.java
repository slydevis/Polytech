package TP6;

import TP7.Commande;
import TP7.CommandeDebut;
import TP7.CommandeFin;

/**
 * Liste Gestion de liste d'entier
 *
 * @author guillaume
 * @version 1.0
 */
public class Listes implements Cloneable, MonIterable{
    private Maillon list;

    public class ListIterator implements InitIterator, InsIterator {
        private Maillon cur;

        public ListIterator() {
            init();
        }

        @Override
        public void init() {
            cur = list;
        }

        @Override
        public void insere(int i) {
            cur = new Maillon(i, cur);
        }

        @Override
        public int courant() {
            return cur.value;
        }

        @Override
        public void suivant() {
            if(!fin())
                cur = cur.next;
        }

        @Override
        public boolean fin() {
            return cur == null;
        }
    }

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
    public Listes(Maillon first) {
        this.list = first;
    }

    /**
     * Constructeur de liste vide
     */
    public Listes() {
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
    public void supprimer(int e) {
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
        else {
            System.out.println("Element introuvable");
            return;
        }
    }

    public void compacter(int n) {
        for(int i = 0; i < n; ++i)
            supprimer(list.value);
    }

    public Listes clone() throws CloneNotSupportedException {
        return (Listes) super.clone();
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

    @Override
    public ListIterator createIterator() {
        return new ListIterator();
    }

    public void afficherTrace(Commande cmd1, Commande cmd2) {
        cmd1.execute(Thread.currentThread().getStackTrace()[1].getMethodName());

        System.out.print("[");
        Maillon maillon = list;
        while(maillon.next != null) {
            System.out.print(maillon.value + ", ");
            maillon = maillon.next;
        }

        System.out.print(maillon.value);
        System.out.print("]\n");

        cmd2.execute(Thread.currentThread().getStackTrace()[1].getMethodName());
    }

    public static void main(String[] args) {
        System.out.println("======= LISTE =======");

        Listes liste = new Listes();
        liste.inserer(3);
        liste.inserer(6);
        liste.inserer(4);
        liste.inserer(3);
        liste.inserer(1);
        liste.inserer(8);
        liste.inserer(9);

        liste.afficher();

        System.out.println("======= ITERATOR ======= ");

        ListIterator iterator = liste.createIterator();
        while(!iterator.fin()) {
            System.out.println(iterator.courant());
            iterator.suivant();
        }

        System.out.println("============================== ");

        try {
            Listes liste2 = liste.clone();
            System.out.println("======= CLONE DE LISTE ======= ");
            liste2.afficher();
            System.out.println("============================== ");

        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }

        liste.supprimer(6);
        liste.afficher();
        liste.supprimer(9);
        liste.afficher();

        liste.compacter(2);

        liste.afficher();

        System.out.println("======= COMMANDE ======= ");

        CommandeDebut c1 = new CommandeDebut() ;
        CommandeFin c2 = new CommandeFin() ;
        liste.afficherTrace(c1, c2);

        System.out.println("============================== ");

        // Vidage de la liste
        System.out.println("Suppresion de tous les éléments");
        liste.supprimer(8);
        liste.supprimer(1);
        liste.supprimer(4);
        liste.supprimer(3);
        liste.afficher();
    }
}