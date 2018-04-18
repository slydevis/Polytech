package TP2;

import TP1.Fenetre;

import javax.swing.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class ConfirmClose {
    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("Fermeture d'une fenetre");

        fenetre.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent windowEvent) {
                int confirmed = JOptionPane.showConfirmDialog(null,
                        "Voulez vous quitter le programme ?", "Confirm ?",
                        JOptionPane.YES_NO_OPTION);

                if (confirmed == JOptionPane.YES_OPTION)
                    fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                else
                    fenetre.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
            }
        });

        fenetre.setVisible(true);
    }
}
