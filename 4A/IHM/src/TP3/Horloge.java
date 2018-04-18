package TP3;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;

public class Horloge extends JPanel {
    private int heure = 0;
    private int minute = 0;
    private PanneauParam param;

    public Horloge(PanneauParam panneauParam) {
        param = panneauParam;
        param.heures.getDocument().addDocumentListener(new HorlogeListener());
        param.minutes.getDocument().addDocumentListener(new HorlogeListener());
    }

    public void paintComponent(Graphics graphics){
        super.paintComponent(graphics);

        Graphics2D g = (Graphics2D) graphics;

        Ellipse2D cercle = new Ellipse2D.Double(0, 0, 300, 300);
        g.draw(cercle);

        // TODO : Center segment
        Double xmin = 100 * Math.sin(Math.toRadians(360 * minute / 60));
        Double ymin = 100 * Math.cos(Math.toRadians(360 * minute / 60));
        Double xheure = 75 * Math.sin(Math.toRadians(360 * (heure * 60 + minute)) / 720);
        Double yheure = 75 * Math.cos(Math.toRadians(360 * (heure * 60 + minute)) / 720);

        Line2D ligne_minute = new Line2D.Double(cercle.getCenterX(), cercle.getCenterY(), cercle.getCenterX() + xmin, cercle.getCenterY() - ymin);
        Line2D ligne_heure = new Line2D.Double(cercle.getCenterX(), cercle.getCenterY(), cercle.getCenterX() + xheure, cercle.getCenterY() - yheure);

        g.draw(ligne_heure);
        g.draw(ligne_minute);
    }

    public class HorlogeListener implements DocumentListener {
        @Override
        public void insertUpdate(DocumentEvent documentEvent) {
            try {
                heure = Integer.parseInt(param.heures.getText());
                minute = Integer.parseInt(param.minutes.getText());
            } catch (NumberFormatException e) {
                heure = 0;
                minute = 0;
            }

            repaint();
        }

        @Override
        public void removeUpdate(DocumentEvent documentEvent) {
            try {
                heure = Integer.parseInt(param.heures.getText());
                minute = Integer.parseInt(param.minutes.getText());
            } catch (NumberFormatException e) {
                heure = 0;
                minute = 0;
            }

            repaint();
        }

        @Override
        public void changedUpdate(DocumentEvent documentEvent) {

        }
    }
}
