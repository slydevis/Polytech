package TP2;

import TP1.Entier;
import TP1.Liste;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Main {
    public static void main(String[] argv) {
    	System.out.println("Création d'un segment");
    	Segment segment = new Segment(new Point(), new Point(1,1));
    	System.out.println("Création d'un cercle");
    	Cercle cercle = new Cercle(new Point(), 5);
    	System.out.println("Création d'un point");
    	Point point = new Point();
    	System.out.println("Création de la pile");
    	Piletransformations pile = new Piletransformations();
    	
    	pile.empiler(point);
    	
    	System.out.println("Dessin du segment et du cercle");
    	segment.dessiner(pile);
    	cercle.dessiner(pile);
    	
    	System.out.println("deplacement de (5,5)");
    	segment.deplacer(new Point(5,5));
    	cercle.deplacer(new Point(5,5));
    	
    	System.out.println("Création d'une image");
    	Image image = new Image();
    	image.ajouter(segment);
    	image.ajouter(cercle);
    	System.out.println("Dessin de l'image");
    	image.dessiner(pile);
    	System.out.println("Deplacement de l'image de (5,5)");
    	image.deplacer(new Point(5,5));
    	System.out.println("Dessin de l'image");
    	image.dessiner(pile);
    	
    	pile.depiler();
    	
    	// Test de l'autre
    	
    	Segment segment2 = new Segment(new Point(), new Point(1,1));
    	Segment segment3 = new Segment(new Point(1,1), new Point(2,3));
    	
    	Cercle cercle2 = new Cercle(new Point(2,3), 42);
    	Cercle cercle3 = new Cercle(new Point(), 3);
    	
    	Point point2 = new Point();
    	
    	Image image2 = new Image();
    	Image image3 = new Image(new Point(3,4));
    	Image image4 = new Image(new Point(5,2));
    	Piletransformations piletransformations = new Piletransformations();
    	
    	piletransformations.empiler(point2);
    	image2.ajouter(segment2);
    	image2.ajouter(cercle2);
    	
    	image3.ajouter(segment3);
    	image3.ajouter(cercle3);
    	
    	image2.dessiner(piletransformations);
    	image3.dessiner(piletransformations);
    	
    	image2.deplacer(new Point(3,1));
    	image3.deplacer(new Point(4,2));
    	
    	image4.ajouter(image3);
    	image4.ajouter(image2);
    	
    	image4.dessiner(piletransformations);
    	
    	piletransformations.depiler();
    	
    	// Creation d'un tableau de structure
    	Structure s[] = new Structure[99];
    	s[0] = new Liste();
    	s[0].inserer(5);
    	s[0].supprimer(5);
    	s[1] = (Structure) new Entier(7);
    	s[1].inserer(8);
    	s[1].supprimer(7);

		Affichable a[]= new Affichable[99];
		a[0] = new Cercle(new Point(0,0), 5);
		a[1] = s[1]; // a[1] = Entier

		a[0].afficher();
		a[1].afficher();

        Compactable c[] = new Compactable[2];
        c[0] = image4;
        c[1] = s[1]; // a[1] = Entier

        c[0].compacter(1);
        c[1].compacter(2);

        System.out.println("Tableau d'image");
        ArrayList<Image> iL = new ArrayList<>();
        image2.ajouter(cercle3);
        iL.add(image2);
        iL.add(image3);
        iL.sort(Image::compareTo);

        for(int i = 0; i < iL.size(); ++i)
            iL.get(i).afficher();

        System.out.println("Image max de la première collection");
        Image imageMax = Collections.max(iL, new Image());
        imageMax.afficher();

        Image imageClone = image4;
    }
}

