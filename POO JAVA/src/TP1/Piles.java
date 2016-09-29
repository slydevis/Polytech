package TP1;

public class Piles {
	private int[] elements; // Le tableau qui contient les nombres entiers
	private int taille; // Indique le nombre max d'éléments que l'on peut stocker dans la pile
	private int nbElements; // Indique combien d'éléments contient la pile
	

	
	
	/**
     * Construit la pile avec la taille passée en paramètre
     * @param taille
     */
    public Piles(int taille) {
        this.taille = taille; // Défini la taille de la nouvelle pile
        elements = new int[taille]; // Créer le tableau qui stockera les valeurs de la table
        nbElements = 0; // Cette pile est vide
    }
    
    
    /**
     * Dit si la pile est pleine
     * @return true si elle est pleine
     */
    public boolean pleine() {
    	return taille==nbElements;
    }
    
    
    /**
     * Dit si la pile est vide
     * @return true si elle est vide
     */
    public boolean vide() {
    	return nbElements==0 ;
    }
    
    
    /**
     * Empile l'entier passé en paramètre
     * @param entier
     */
    public void empiler(int entier) {
    	assert !pleine(); // Renvoie une erreur si la pile est pleine
    	
    	elements[nbElements] = entier; // Rajoute l'entier dans le dernier emplacement libre de la pile
    	++nbElements; // Met à jour le nombre d'éléments de la pile
    }
    
    /**
     * Dépile l'entier en haut de la pile
     * @return sommet
     */
    public int depiler() {
    	assert !vide(); // Renvoie une erreur si la pile est vide
    	
    	--nbElements; // Décrémente le nombre d'éléments, permettant d'écrire à l'emplacement du sommet
    	return elements[nbElements]; // Renvoie le sommet
    }
    
    
    
    /**
     * Fonction de test
     */
    public static void main(String[] args) {
        
    	int sommet;
        // Déclaration d'une nouvelle pile
        Piles pileA = new Piles(4);

        pileA.empiler(4);
        sommet = pileA.depiler();
        
        System.out.println(sommet);

    }

}
