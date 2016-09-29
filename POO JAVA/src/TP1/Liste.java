package TP1;

import TP2.Structure;

public class Liste extends Structure {
	// Un liste est composée de maillons chainées entre eux
	
	// On créer la classe privée des maillons
	class maillons {
		public int valeur;
		public maillons suivant;
		
		
		/**
		 * Constructeur du maillon
		 * @param valeur
		 * @param suivant
		 */
		public maillons(int valeur, maillons suivant) {
			this.valeur = valeur;
			this.suivant = suivant;
		}
		
		/**
         * affiche dans la console les données du maillon et de ses suivants
         */
        public void print() {
            System.out.print(valeur + " -> ");

            if (suivant != null) {
                suivant.print();
            }
        }
	}
	
	
	// A partir de là, on définie la classe liste
	private maillons premier; // La liste ne stocke que cet élément : le premier maillon de la chaine
	
	
	/**
	 * Constructeur de la liste vide
	 */
	public Liste() {
		premier = null;
	}
	
	
	/**
     * Insère un entier à liste si sa valeur n'est pas déjà présente
     * @param entier
     */
    public void inserer(int entier) {

        // On regarde si cet entier n'est pas déjà présent dans la liste
        int estPresent = 0; // 0 si absent, 1 si présent dans la liste
        
        maillons mParcours = premier; // le maillons qui va "parcourir" la liste

        while (mParcours != null) {
            if (mParcours.valeur == entier) {
                estPresent = 1 ;
            }
            mParcours = mParcours.suivant;
        }

        // Si cet entier est absent de la liste, on l'ajoute
        if (estPresent == 0) {
            maillons nouveauMaillon = new maillons(entier, premier);
            premier = nouveauMaillon;
        }
    }
    
    
    /**
     * Supprime un entier de liste si sa valeur est présente
     * @param entier
     */
    public void supprimer(int entier) {
    	
    	maillons mParcours = premier; // le maillons qui va "parcourir" la liste
    	
    	// Si l'entier est dans le premier maillon
        if (mParcours != null && mParcours.suivant != null && mParcours.valeur == entier) {
            premier = mParcours.suivant;
            return;
        }

        // Si il n'y qu'un seul maillon
        if (mParcours != null && mParcours.suivant == null && mParcours.valeur == entier) {
            premier = null;
            return;
        }

        // On recherche dans tout le reste de la liste
        while (mParcours != null) {
            if (mParcours.suivant != null && mParcours.suivant.valeur == entier) {
            	mParcours.suivant = mParcours.suivant.suivant; //on saute le maillon qui contient l'entier
            	return;
            }
            mParcours = mParcours.suivant;
        }

    }
    
    
    /**
     * Afficher la liste dans la console
     */
    public void print() {
        premier.print();
        System.out.println();
    }
    
    
    /**
     * Fonction de test
     */
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
