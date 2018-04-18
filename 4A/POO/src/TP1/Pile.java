package TP1;

import TP3.HorsLimites;
import TP3.PileVide;

import java.lang.reflect.Array;
import java.util.ArrayDeque;

/**
 * Pile Permer de gérer une pile de nombre entiers
 *
 * @author guillaume
 * @version 1.0
 */
public class Pile<E> {
    private E data[];
    private int size = 0;
    private int nbElem = 0;

    public Pile(int size, Class<E> c) {
        this.size = size;
        this.data = (E[]) Array.newInstance(c, size);
    }
    /**
     * Construit une pile de taille donnée
     *
     * @param size taille de la pile
     */
    public Pile(int size) {
        this.size = size;
        this.data = (E[]) new Object[size];
    }

    public int getTab(int i) throws HorsLimites {
        if(i < 0 || i >= size)
            throw new HorsLimites(i);
        else
            return i;
    }

    /**
     * Empile un nouvelle élément dans la pile si elle n'est pas pleine
     *
     * @param e élément à empiler
     */
    public void empiler(E e) {
        if (!plein()) {
            data[nbElem] = e;
            nbElem++;
        }
    }

    /**
     * Dépile le dernier élément de la pile et le renvoie
     *
     * @return Dernier élément de la pile
     */
    public E depiler() throws PileVide {
        if (vide())
            throw new PileVide();

        nbElem--;
        return data[nbElem];
    }

    /**
     * Test si la pile est pleine
     *
     * @return Renvoie true si la pile est pleine
     */
    public boolean plein() {
        return nbElem == size;
    }

    /**
     * Test si la pile est vide
     *
     * @return Renvoie true si la pile est vide
     */
    public boolean vide() {
        return nbElem == 0;
    }

    public static void main(String[] args) {
        System.out.println("======= PILE =======");

        Pile<Integer> pile = new Pile<>(3, Integer.class);
/*
        try {
            System.out.println(pile.depiler());
        } catch (PileVide pileVide) {
            pileVide.printStackTrace();
        }*/

        pile.empiler(4);
        pile.empiler(9);
        pile.empiler(10);
        pile.empiler(11);
        pile.empiler(12);

        try {
            System.out.println(pile.depiler());
        } catch (PileVide pileVide) {
            pileVide.printStackTrace();
        }

        ArrayDeque<String> arrayDeque = new ArrayDeque<>(10);
        arrayDeque.add("h");
        arrayDeque.add("e");
        arrayDeque.add("l");
        arrayDeque.add("l");
        arrayDeque.add("o");

        System.out.println("arrayDeque = " + arrayDeque.toString());
    }
}
