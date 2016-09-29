package TP1;

import java.util.Arrays;

import TP2.Structure;

public class Entier extends Structure {
	private int[] elements; // Le tableau qui contient les nombres entiers
	private int taille; // Indique le nombre max d'éléments que l'on peut stocker dans la pile
	private int nbElements; // Indique combien d'éléments contient la pile
	
	
	
	
	/**
     * Construit la table avec la taille passée en paramètre
     * @param taille
     */
    public Entier(int taille) {
        this.taille = taille; // Défini la taille du nouveau tableau
        elements = new int[taille]; // Créer le tableau qui stockera les valeurs de la table
        nbElements = 0; // Ce tableau est vide
    }
    
    
    /**
     * insère l'élément passé en paramètre s'il n'est pas déjà présent
     * @param entier
     */
    public void inserer(int entier) {
    	// On cherche à partir d'où, les valeurs sont plus grande quel'entier à ajouter
        int i = 0;
        while (i < nbElements) {
            if (entier < elements[i]) {
                break;
            }
            ++i;
        }
        
        // on vérifie que la valeur n'existe pas dans le tableau
        if (entier != elements[i])
        {
        	 assert nbElements < taille; // Le tableau n'est pas encore plein
        	 
        	 
        	 // On libère l'emplacement en déplacant tous les éléments après i d'un cran vers la droite
        	 for (int j = nbElements ; j>i ; --j)
        	 {
        		 elements[j] = elements[j-1];
        	 }
        	 
        	 // On ajoute l'entier au bon emplacement i
        	 elements[i] = entier;
        	 
        	 // On met à jour le nombre d'éléments du tableau
        	 ++nbElements;
        }
    }
    
    /**
     * Supprime la valeur du tableau, si elle est présente
     * @param entier
     */
    public void supprimer(int entier)
    {
    	assert nbElements > 0 ; //on vérifie qu'il y est des éléments dans le tableau
    	
    	// On cherche le rang de la valeur à supprimer, en même on vérifie si cette valeur est présente 
        int i = 0;
        while (i < nbElements) {
            if (elements[i] == entier) {
                break;
            }
            ++i;
        }
        
        // On supprime l'élément du tableau si il est présent
        if (i < nbElements) {
        	for (int j = i ; j < nbElements ; ++j) {
        		elements[j] = elements[j+1];
        	}
        	--nbElements; // On met à jour le nombre d'éléments
        }
    }
    
    
    /**
     * Affiche un tableau d'entier dans le terminal
     */
    public void print() {
        System.out.println(Arrays.toString(elements));
    }
    
    
    /**
     * Fonction de test
     */
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
