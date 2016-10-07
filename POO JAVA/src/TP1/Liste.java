package TP1;

import TP2.Structure;

public class Liste extends Structure {
    private Maillons premier;

    public Liste() {
        premier = null;
    }

    class Maillons {
        public int valeur;
        public Maillons next;

        public Maillons(int valeur, Maillons next) {
            this.valeur = valeur;
            this.next = next;
        }

        public void print() {
            System.out.println(valeur + " -> ");
            if(next != null)
                next.print();
        }
    }

    public void inserer(int entier) {
        boolean estPresent = false;
        Maillons maillons = premier;

        while(maillons != null) {
            if(maillons.valeur == entier)
                estPresent = true;
            maillons = maillons.next;
        }

        if(!estPresent) {
            Maillons newMaillons = new Maillons(entier, premier);
            premier = newMaillons;
        }
    }

    public void supprimer(int entier) {
        Maillons maillons = premier;

        if(maillons != null && maillons.next != null && maillons.valeur == entier) {
            premier = maillons.next;
            return;
        }

        if(maillons != null && maillons.next == null && maillons.valeur == entier) {
            premier = null;
            return;
        }

        while (maillons != null) {
            if(maillons.next != null && maillons.next.valeur == entier) {
                maillons.next = maillons.next.next;
                return;
            }
            maillons = maillons.next;
        }
    }

    public void print() {
        premier.print();
        System.out.println();
    }

    public static void main(String[] args) {

        Liste liste1 = new Liste();

        liste1.inserer(2);
        liste1.print();
        liste1.inserer(3);
        liste1.inserer(5);
        liste1.inserer(7);
        liste1.inserer(11);
        liste1.print();
        liste1.supprimer(7);
        liste1.print();
        liste1.supprimer(2);
        liste1.print();
        liste1.supprimer(11);
        liste1.print();

    }
}
