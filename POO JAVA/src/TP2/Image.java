package TP2;

import java.util.Comparator;

public class Image extends Forme implements Compactable, Comparable<Image>, Comparator<Image> {
    private final int MAX_ITEMS = 100;
    private Forme[] formesCollec;
    private Point pOrigin;
    private int nbFormes;

    public Image() {
        formesCollec = new Forme[MAX_ITEMS];
        nbFormes = 0;
        pOrigin = new Point();
    }

    public Image(Point p) {
        this(); // On utilise le constructeur par défault
        pOrigin = p;
    }

    public void ajouter(Forme f) {
        formesCollec[nbFormes] = f;
        nbFormes++;
    }

    public Point getOrigin() {
        return this.pOrigin;
    }

    @Override
    public void dessiner(Piletransformations pt) {
        System.out.println("Image :");
        System.out.println("pOrigin :" + pOrigin.additionner(pt.getCourant()));

        for(int i = 0; i < nbFormes; ++i) {
        	Forme f = formesCollec[i];
            f.dessiner(pt);
        }
    }

    @Override
    public void deplacer(Point p) {
        pOrigin = pOrigin.additionner(p);
    }

    @Override
    public void afficher() {
        System.out.println("Image ======================");
        System.out.println("NB formes = " + nbFormes);
        System.out.println("Point d'origine = " + pOrigin);

        for(int i = 0; i < nbFormes; ++i)
            formesCollec[i].afficher();
    }

    @Override
    public void compacter(int nb) {
        nbFormes-=nb;
    }

    public int getNbForme() { return nbFormes; }

    @Override
    public int compareTo(Image o) {
        if(getNbForme() < o.getNbForme())
            return -1;
        else if(getNbForme() == o.getNbForme())
            return 0;

        return 1;
    }

    // implementer une methode max dans l'api
    @Override
    public int compare(Image o1, Image o2) {
        if(o1.getOrigin().getY() < o2.getOrigin().getY())
            return -1;
        else if(o1.getOrigin().getY() == o2.getOrigin().getY())
            return 0;
        return 1;
    }
}
