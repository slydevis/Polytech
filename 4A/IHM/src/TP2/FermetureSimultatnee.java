package TP2;

import TP1.Fenetre;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class FermetureSimultatnee extends JPanel {
    private ArrayList<JFrame> fenetres;

    public static final int FRAME_WIDTH = 200;
    public static final int FRAME_HEITH = 200;

    public int last_x = 100;
    public int last_y = 100;

    private JButton cree_button;
    private JButton fermer_button;

    public FermetureSimultatnee() {
        fenetres = new ArrayList<>();
        cree_button = new JButton("CREER");
        fermer_button = new JButton("FERMER");
        this.add(cree_button);
        this.add(fermer_button);

        cree_button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                JFrame fenetre = new JFrame("Fenetre + " + fenetres.size());
                fenetre.setBounds(last_x, last_y, FRAME_WIDTH, FRAME_HEITH);
                fenetre.setVisible(true);

                fenetres.add(fenetre);

                last_x += 10;
                last_y += 10;
            }
        });

        fermer_button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                for (JFrame frame : fenetres) {
                    frame.dispose();
                }

                fenetres.clear();
                last_x = 100;
                last_y = 100;
            }
        });
    }

    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("Fermeture simultannee de fenetres");
        FermetureSimultatnee panneau = new FermetureSimultatnee();

        fenetre.setContentPane(panneau);
        fenetre.setVisible(true);
    }
}
