package TP2;

import TP1.Fenetre;

import javax.swing.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;

public class MouvementSouris {
    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("Mouvement de souris");
        JPanel panel = new JPanel();

        panel.addMouseMotionListener(new MouseMotionAdapter() {
            public void mouseMoved(MouseEvent mouseEvent) {
                panel.getGraphics().drawRect(mouseEvent.getX(), mouseEvent.getY(), 20, 20);
            }
        });

        fenetre.setContentPane(panel);
        fenetre.setVisible(true);
    }
}
