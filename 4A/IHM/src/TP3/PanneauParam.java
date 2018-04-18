package TP3;

import javax.swing.*;

public class PanneauParam extends JPanel {
    private JLabel mot_heure;
    private JLabel mot_minute;
    public JTextField heures;
    public JTextField minutes;

    public PanneauParam() {
        mot_heure = new JLabel("Heures : ");
        add(mot_heure);
        heures = new JTextField("0", 3);
        add(heures);
        heures.getDocument().putProperty("heures", heures);

        mot_minute = new JLabel("Minutes : ");
        add(mot_minute);
        minutes = new JTextField("0", 3);
        add(minutes);
        minutes.getDocument().putProperty("minutes", minutes);
    }
}
