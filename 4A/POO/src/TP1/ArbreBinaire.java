package TP1;

/**
 * ArbreBinaire Gestion d'un arbre binaire
 *
 * @author guillaume
 * @version 1.0
 */
public class ArbreBinaire extends Noeud {
    /**
     * Création d'un arbre binaire vide
     */
    private ArbreBinaire() {

    }

    /**
     * Constructeur d'un arbre vide avec une racine
     *
     * @param e valeur de la racine
     */
    public ArbreBinaire(int e) {
        this(e, null, null);
    }

    /**
     * Constructeur d'un arbre à partie avec des sous-arbres
     *
     * @param e  valeur du noeud ou de la feuille
     * @param fg sous-arbre gauche
     * @param fd sous-arbre droite
     */
    public ArbreBinaire(int e, Noeud fg, Noeud fd) {
        this.val = e;
        this.fg = fg;
        this.fd = fd;
    }

    /**
     * Methode récursive pour inserer un nouvelle élément dans un arbre
     *
     * @param e     valeur entière à insérer dans l'arbre
     * @param noeud Noeud de l'arbre à insérer
     */
    private void insererRec(int e, Noeud noeud) {
        if (e > noeud.val) {
            if (noeud.fd == null)
                noeud.fd = new Noeud(e);
            else
                insererRec(e, noeud.fd);
        }
        if (e < noeud.val) {
            if (noeud.fg == null)
                noeud.fg = new Noeud(e);
            else
                insererRec(e, noeud.fg);
        }
    }

    /**
     * Insére un nouvelle entier dans l'arbre binaire
     *
     * @param e valeur à insérer
     */
    public void inserer(int e) {
        insererRec(e, this);
    }

    /**
     * Supprime le noeud minimum de l'arbre
     * @param noeud
     * @return
     */
    private Noeud deleteMin(Noeud noeud) {
        if (noeud.fg == null) {
            return noeud.fd;
        }
        noeud.fg = deleteMin(noeud.fg);
        return noeud;
    }

    /**
     * Récupère le noeud minimum de l'arbre
     * @param noeud
     * @return
     */
    private Noeud min(Noeud noeud) {
        if (noeud.fg == null) {
            return noeud;
        }
        else {
            return min(noeud.fg);
        }
    }

    /**
     * @param e
     * @param noeud
     * @return
     */
    private Noeud supprimerRec(int e, Noeud noeud) {
        if (noeud.val < e) {
            noeud.fd = supprimerRec(e, noeud.fd);
        }
        else if (noeud.val > e) {
            noeud.fg = supprimerRec(e, noeud.fg);
        }
        else {
            if (noeud.fd == null)
                return noeud.fg;

            if (noeud.fg == null)
                return noeud.fd;

            Noeud temp = noeud;
            noeud = min(temp.fd);
            noeud.fd = deleteMin(temp.fd);
            noeud.fg = temp.fg;
        }

        return noeud;
    }

    /**
     * Supprime un élémént dans l'arbre si il existe
     *
     * @param e valeur à supprimer
     */
    public void supprimer(int e) {
        Noeud ret = supprimerRec(e, this);

        if (ret == null) {
            this.val = 0;
            this.fd = null;
            this.fg = null;
        }
        else {
            this.val = ret.val;
            this.fg = ret.fg;
            this.fd = ret.fd;
        }
    }

    /**
     * Affiche un arbre binaire dans la sortie standard
     *
     * @param tree  arbre à afficher
     * @param level nombre de parent (pour l'indentation)
     */
    public void afficher(Noeud tree, int level) {
        int i;
        if (tree != null) {
            afficher(tree.fd, level + 1);
            for (i = 0; i < level; i++) {
                System.out.printf("    ");
            }

            if (tree.fd == null && tree.fg == null)
                System.out.printf("%d\n", tree.val);
            else
                System.out.printf("%d\n", tree.val);

            afficher(tree.fg, level + 1);
        }
    }

    public static void main(String[] args) {
        System.out.println("======= ARBRE BINAIRE =======");

        ArbreBinaire arbreBinaire = new ArbreBinaire(8);

        arbreBinaire.inserer(8);
        arbreBinaire.inserer(5);
        arbreBinaire.inserer(6);
        arbreBinaire.inserer(4);
        arbreBinaire.inserer(11);
        arbreBinaire.inserer(7);
        arbreBinaire.inserer(9);
        arbreBinaire.inserer(1);
        arbreBinaire.inserer(12);
        arbreBinaire.inserer(3);
        arbreBinaire.inserer(2);

        arbreBinaire.afficher(arbreBinaire, 0);

        System.out.println("SUPPRESSION DE 5");
        arbreBinaire.supprimer(5);

        arbreBinaire.afficher(arbreBinaire, 0);

        System.out.println("Création d'un arbre vide");
        ArbreBinaire arbreVide = new ArbreBinaire();
        arbreVide.afficher(arbreVide, 0);

    }
}
