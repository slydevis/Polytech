package TP2;

import TP4.MyInfo;

import java.util.Comparator;

@MyInfo(annee = 2045)
public class Image extends Forme implements Compactable, Comparable<Image>, Comparator<Image> {
    private final int MAX_ITEM = 100;
    private Forme[] formesCollec;
    private int nbFormes = 0;

    public Image() {
        super();
        this.formesCollec = new Forme[MAX_ITEM];
    }

    public Image(Point p) {
        super(p);
        this.formesCollec = new Forme[MAX_ITEM];
    }

    public int getNbFormes() {
        return this.nbFormes;
    }

    public void ajouter(Forme forme) {
        if (nbFormes < MAX_ITEM) {
            formesCollec[nbFormes] = forme;
            nbFormes++;
        }
        else {
            System.out.println("L'image est pleine");
        }
    }

    @Override
    public void dessiner(Piletransformations piletransformations) {
        System.out.println("Image :");
        System.out.println("pOrigin = " + super.getOrigin().additionner(piletransformations.getCourant()));

        for (int i = 0; i < nbFormes; ++i) {
            Forme f = formesCollec[i];
            f.dessiner(piletransformations);
        }
    }

    @Override
    public void afficher() {
        System.out.println("Image :");
        System.out.println("pOrigin = " + getOrigin());

        for (int i = 0; i < nbFormes; ++i) {
            Forme f = formesCollec[i];
            f.afficher();
        }
    }

    @Override
    public void compacter(int n) {
        nbFormes -= n;
    }

    @Override
    public int compareTo(Image image) {
        if(getNbFormes() < image.getNbFormes())
            return -1;
        else if (getNbFormes() == image.getNbFormes())
            return 0;
        else
            return 1;
    }

    @Override
    public int compare(Image image, Image image2) {
        if(image.getOrigin().getY() < image2.getOrigin().getY())
            return -1;
        else if(image.getOrigin().getY() == image2.getOrigin().getY())
            return 0;
        else
            return 1;
    }

    public static void main(String[] args) {
        Image image = new Image();
        Piletransformations piletransformations = new Piletransformations();
        piletransformations.empiler(new Point(2, 2));
        image.ajouter(new Cercle(new Point(2, 2), 2));
        image.dessiner(piletransformations);
        image.afficher();

        // Test de créer une image pleine
        Image imagePleine = new Image();
        for(int i = 0; i < 101; ++i)
            imagePleine.ajouter(new Cercle(new Point(2, 2), 3));

        image.afficher();


        // CompareTo Test
        if(imagePleine.compareTo(image) == 1)
            System.out.println("L'image pleine est plus lourde que la première image");
        if(image.compareTo(imagePleine) == -1)
            System.out.println("L'image pleine est plus lourde que la première image");
        if(image.compareTo(image) == 0)
            System.out.println("La variable image est aussi lourde que elle même");

        // Test compare
        Image imagePetit = new Image(new Point(0, 1));
        Image imagePlusHaute = new Image(new Point(0, 2));

        if(imagePetit.compare(imagePlusHaute, imagePetit) == 1)
            System.out.println("La première image est plus haute");
        if(imagePlusHaute.compare(imagePetit, imagePlusHaute) == -1)
            System.out.println("La deuxième image est plus haute");
        if(imagePetit.compare(imagePetit, imagePetit) == 0)
            System.out.println("Les deux images sont au même ordonnée");
    }
}
