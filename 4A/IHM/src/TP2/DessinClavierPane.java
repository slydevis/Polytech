package TP2;

import TP1.Fenetre;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.util.ArrayList;

public class DessinClavierPane extends JPanel {
    private ArrayList<Line2D> lines = new ArrayList<>();

    public DessinClavierPane(ArrayList<Line2D> tab) {
        lines = tab;
    }

    public void paintComponent(Graphics graphics) {
        Graphics2D g = (Graphics2D) graphics;

        g.setStroke(new BasicStroke(5));
        for(Line2D line : lines)
            g.draw(line);
    }

    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("Dessin avec le clavier");

        ArrayList<Line2D> lines = new ArrayList<>();

        DessinClavierPane dessinClavierPane = new DessinClavierPane(lines);

        lines.add(new Line2D.Double(0,0,0,0));

        fenetre.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent keyEvent) {
                super.keyPressed(keyEvent);

                Point2D begin, end = null;
                begin = lines.get(lines.size() - 1).getP2();

                int delta = 10;

                if(keyEvent.isShiftDown())
                    delta = 50;

                switch(keyEvent.getKeyCode()) {
                    case KeyEvent.VK_H:
                    case KeyEvent.VK_UP:
                        end = new Point2D.Double(begin.getX(), begin.getY() - delta);
                        break;
                    case KeyEvent.VK_J:
                    case KeyEvent.VK_RIGHT:
                        end = new Point2D.Double(begin.getX() + delta, begin.getY());
                        break;
                    case KeyEvent.VK_K:
                    case KeyEvent.VK_DOWN:
                        end = new Point2D.Double(begin.getX(), begin.getY() + delta);
                        break;
                    case KeyEvent.VK_L:
                    case KeyEvent.VK_LEFT:
                        end = new Point2D.Double(begin.getX() - delta, begin.getY());
                        break;
                    default:
                        break;
                }

                if(end != null)
                    lines.add(new Line2D.Double(begin, end));

                dessinClavierPane.repaint();
            }
        });

        fenetre.setContentPane(dessinClavierPane);
        fenetre.setVisible(true);
    }
}
