package TP1;

import java.util.Arrays;

import TP2.Structure;

public class Entier extends Structure {
	private int[] elements;
	private int taille;
	private int nbElements = 0;

    public Entier(int taille) {
        this.taille = taille;
        elements = new int[taille];
    }

    public void inserer(int entier) {
        int i;
        for(i = 0; i < nbElements; ++i) {
            if(entier < elements[i])
                break;
        }

        if (entier != elements[i]) {
            assert nbElements < taille;

            for(int j = nbElements; j>i; --j)
            elements[j] = elements[j-1];

            elements[i] = entier;
            ++nbElements;
        }
    }

    public void supprimer(int entier) {
    	assert nbElements > 0 ;

        int i = 0;
        for(; i < nbElements; ++i)  {
            if(elements[i] == entier)
                break;
        }
        
        if (i < nbElements) {
        	for (int j = i; j < nbElements; ++j)
        		elements[j] = elements[j+1];
        	--nbElements;
        }
    }
    
    public void print() {
        System.out.println(Arrays.toString(elements));
    }
    
    public static void main(String[] args) {
        Entier tableau1 = new Entier(10);

        tableau1.inserer(10);
        tableau1.print();
        tableau1.inserer(7);
        tableau1.inserer(0);
        tableau1.inserer(3);
        tableau1.print();
        tableau1.supprimer(7);
        tableau1.print();
        tableau1.supprimer(5);
        tableau1.print();
    }
}
