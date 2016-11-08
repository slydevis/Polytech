package TP1;

import TP3.PileVide;

import java.lang.reflect.Array;
import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Objects;

public class Piles<E> {
    private E[] data;
    private int maxElement;
    private int nbElement = 0;

    public Piles(int taille, Class<E> c) {
        maxElement = taille;
        data = (E[]) Array.newInstance(c, maxElement);
    }
    /**
     * Constructeur de la classe Piles
     * @param taille
     */
    public Piles(int taille) {
        maxElement = taille;
        data = (E[]) new Object[maxElement];
    }

    /**
     * Empile un élément sur la pile
     * @param element
     */
    public void empiler(E element) {
        assert !pleine();
        data[nbElement] = element;
        nbElement++;
    }

    /**
     * Dépile l'entier du sommet de la pile
     * @return le sommet
     * @throws PileVide
     */
    public E depiler() throws PileVide {
        if (vide())
            throw new PileVide();
        nbElement--;
        return data[nbElement];
    }

    /**
     * @return true si la pile est pleine
     */
    private boolean pleine() {
        return nbElement == maxElement;
    }

    /**
     * @return true si la pile est vide
     */
    private boolean vide() {
        return nbElement == 0;
    }

    public static void main(String[] args) {
        try {
            Piles<Integer> piles = new Piles<>(4);
            piles.empiler(5);
            System.out.println("Sommet = " + piles.depiler());

            /* Test de la mécanisme de réflexion */
            Piles<String> stringPiles = new Piles(4, String.class);
            stringPiles.empiler("C'est du JAVA");
            System.out.println("Sommet = " + stringPiles.depiler());
        } catch (PileVide pileVide) {
            pileVide.printStackTrace();
        }

        /* ArrayDeque */
        System.out.println("Même pile de String avec ArrayDeque");
        ArrayDeque<String> arrayDeque = new ArrayDeque<>();
        arrayDeque.push("J'aime les licornes");
        System.out.println("Sommet = "  + arrayDeque.pop());

    }
}