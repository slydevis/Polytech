package TP2;

import TP1.Fenetre;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ButtonClicMain {
    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("Clic sur un bouton");
        JPanel panel = new JPanel();

        JButton rButton = new JButton("R");
        JButton jButton = new JButton("J");
        JButton bButton = new JButton("B");

        rButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                panel.setBackground(Color.RED);
            }
        });

        bButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                panel.setBackground(Color.BLUE);
            }
        });

        jButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                panel.setBackground(Color.YELLOW);
            }
        });

        panel.add(rButton);
        panel.add(jButton);
        panel.add(bButton);

        fenetre.setContentPane(panel);
        fenetre.setVisible(true);
    }
}
