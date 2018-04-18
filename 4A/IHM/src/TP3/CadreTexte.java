package TP3;

import TP1.Fenetre;

import javax.swing.*;
import java.awt.*;

public class CadreTexte extends JPanel {
    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("CadreTexte", 303, 380);

        PanneauParam panneauParam = new PanneauParam();
        Horloge horloge = new Horloge(panneauParam);

        fenetre.add(panneauParam, BorderLayout.SOUTH);
        fenetre.add(horloge, BorderLayout.CENTER);

        fenetre.setVisible(true);
    }
}
