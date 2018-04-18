package TP3;

import TP1.Fenetre;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Menu extends JMenuBar {
    PanneauDessin panneauDessin;
    public Menu(PanneauDessin panneauDessin) {
        this.panneauDessin = panneauDessin;
        addFormeMenu();
        addDimensionMenu();
        addCouleurMenu();
    }

    public void addFormeMenu() {
        JMenu menuForme = new JMenu("Forme");
        JMenuItem itemCercle = new JMenuItem("Cercle");
        JMenuItem itemRectangle = new JMenuItem("Rectangle");

        itemCercle.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                panneauDessin.setForme("cercle");
                panneauDessin.repaint();
            }
        });

        itemRectangle.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                panneauDessin.setForme("rectangle");
                panneauDessin.repaint();
            }
        });

        menuForme.add(itemCercle);
        menuForme.add(itemRectangle);
        add(menuForme);
    }

    public void addDimensionMenu() {
        JMenu menuDimension = new JMenu("Dimension");
        JMenuItem itemPetit = new JMenuItem("Petit");
        JMenuItem itemGrand = new JMenuItem("Grand");

        itemPetit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                panneauDessin.setDimension(new Dimension(20, 20));
                panneauDessin.repaint();
            }
        });

        itemGrand.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                panneauDessin.setDimension(new Dimension(300, 200));
                panneauDessin.repaint();
            }
        });

        menuDimension.add(itemPetit);
        menuDimension.add(itemGrand);
        add(menuDimension);
    }

    public void addCouleurMenu() {
        JMenu menuCouleur = new JMenu("Couleur");
        JMenuItem itemRouge = new JMenuItem("Rouge");
        JMenuItem itemBleu = new JMenuItem("Bleu");

        itemRouge.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                panneauDessin.setCouleur(Color.RED);
                panneauDessin.repaint();
            }
        });

        itemBleu.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                panneauDessin.setCouleur(Color.BLUE);
                panneauDessin.repaint();
            }
        });

        menuCouleur.add(itemRouge);
        menuCouleur.add(itemBleu);
        add(menuCouleur);
    }

    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("Menu");

        PanneauDessin panneauDessin = new PanneauDessin();
        Menu menu = new Menu(panneauDessin);

        fenetre.setJMenuBar(menu);
        fenetre.setContentPane(panneauDessin);

        fenetre.setVisible(true);
    }
}
