package TP1;

public class ArbreBinaire {
    private ArbreBinaire filsDroit = null;
    private ArbreBinaire filsGauche = null;
    private int valeur;

    // On bloque volontaire la création avec le constructeur de base
    private ArbreBinaire() {

    }

    public ArbreBinaire(int entier, ArbreBinaire fd, ArbreBinaire fg) {
        valeur = entier;
        filsDroit = fd;
        filsGauche = fg;
    }

    public ArbreBinaire(int entier) {
        this(entier, null, null);
    }

    /**
     * @param entier à inserer dans l'arbre binaire
     */
    public void inserer(int entier) {
        if(entier > valeur) {
            if(filsGauche == null)
                filsGauche = new ArbreBinaire(entier);
            else
                filsGauche.inserer(entier);
        }
        else if(entier < valeur) {
            if(filsDroit == null)
                filsDroit = new ArbreBinaire(entier);
            else
                filsDroit.inserer(entier);
        }
    }

    /**
     * @param entier à supprimer dans l'arbre binaire
     */
    public void supprimer(int entier) {
        if(entier > valeur) {
            if(filsGauche != null)
                filsGauche.supprimer(entier);
        }
        else if(entier < valeur) {
            if(filsDroit != null)
                filsDroit.supprimer(entier);
        }
        else {
            if(filsDroit != null) {
                valeur = filsDroit.valeur;
                filsDroit = null;
            }
            else if(filsGauche != null) {
                valeur = filsGauche.valeur;
                filsGauche = null;
            }
        }
    }

    /**
     * @param arbre affiche l'arbre courant (récursif)
     */
    public void afficher(ArbreBinaire arbre) {
        if(arbre.filsGauche != null)
            afficher(arbre.filsGauche);

        System.out.println("Cle = " + arbre.valeur);

        if(arbre.filsDroit != null)
            afficher(arbre.filsDroit);
    }

    public static void main(String[] args) {
        ArbreBinaire arbreBinaire = new ArbreBinaire(8);
        arbreBinaire.inserer(4);
        arbreBinaire.inserer(50);
        arbreBinaire.inserer(3);
        arbreBinaire.inserer(2);
        arbreBinaire.afficher(arbreBinaire);
        System.out.println("Suppression du 3 : ");
        arbreBinaire.supprimer(3);
        arbreBinaire.afficher(arbreBinaire);
    }
}
