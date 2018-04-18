package TP2;

import TP1.Fenetre;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;

public class DeplacementSourisPanneau extends JPanel {
    private ArrayList<Rectangle2D> rectangles;
    public static final double SQUARE_SIZE = 20;
    public static final double SQUARE_OFFSET = DeplacementSourisPanneau.SQUARE_SIZE / 2;

    public Rectangle2D last_dragged = null;
    public int last_i = 0;

    public DeplacementSourisPanneau() {
        rectangles = new ArrayList<>();
    }

    @Override
    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);

        Graphics2D g = (Graphics2D) graphics;

        g.setStroke(new BasicStroke(5));
        System.out.println("SIZE = " + rectangles.size());

        for (Rectangle2D rectangle : rectangles)
            g.draw(rectangle);
    }

    public void addRectangle(double posX, double posY) {
        System.out.println("[" + posX + ", " + posY + ']');
        rectangles.add(new Rectangle2D.Double(posX - SQUARE_OFFSET, posY - SQUARE_OFFSET, SQUARE_SIZE, SQUARE_SIZE));
    }

    public ArrayList<Rectangle2D> getRectangles() {
        return this.rectangles;
    }

    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("Clic et déplacement avec la souris");
        DeplacementSourisPanneau panneau = new DeplacementSourisPanneau();

        panneau.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseMoved(MouseEvent mouseEvent) {
                super.mouseMoved(mouseEvent);

                ArrayList<Rectangle2D> rectangles = panneau.getRectangles();
                for (Rectangle2D rectangle : rectangles) {
                    if (mouseEvent.getX() >= rectangle.getMinX()
                            && mouseEvent.getX() <= rectangle.getMaxX()
                            && mouseEvent.getY() >= rectangle.getMinY()
                            && mouseEvent.getY() <= rectangle.getMaxY())
                        panneau.setCursor(Cursor.getPredefinedCursor(Cursor.CROSSHAIR_CURSOR));
                    else
                        panneau.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
                }
            }

            @Override
            public void mouseDragged(MouseEvent mouseEvent) {
                super.mouseDragged(mouseEvent);

                if (panneau.last_dragged != null) {
                    Rectangle2D carre = panneau.last_dragged;
                    carre.setRect(mouseEvent.getX() - SQUARE_OFFSET, mouseEvent.getY() - SQUARE_OFFSET, SQUARE_SIZE, SQUARE_SIZE);
                    panneau.getRectangles().set(panneau.last_i - 1, carre);
                }
                else {
                    panneau.last_i = 0;
                    for (Rectangle2D rectangle : panneau.getRectangles()) {
                        if (mouseEvent.getX() >= rectangle.getMinX()
                                && mouseEvent.getX() <= rectangle.getMaxX()
                                && mouseEvent.getY() >= rectangle.getMinY()
                                && mouseEvent.getY() <= rectangle.getMaxY()) {
                            Rectangle2D carre = rectangle;
                            carre.setRect(mouseEvent.getX() - SQUARE_OFFSET, mouseEvent.getY() - SQUARE_OFFSET, SQUARE_SIZE, SQUARE_SIZE);
                            panneau.last_dragged = carre;
                            panneau.getRectangles().set(panneau.last_i, carre);
                        }
                        ++panneau.last_i;
                    }
                }


                panneau.revalidate();
                panneau.repaint();
            }
        });

        panneau.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent mouseEvent) {
                super.mouseClicked(mouseEvent);

                if (mouseEvent.getClickCount() == 2) {
                    System.out.println("Double click");

                    ArrayList<Rectangle2D> rectangles = panneau.getRectangles();
                    for (Rectangle2D rectangle : rectangles) {
                        if (mouseEvent.getX() >= rectangle.getMinX()
                                && mouseEvent.getX() <= rectangle.getMaxX()
                                && mouseEvent.getY() >= rectangle.getMinY()
                                && mouseEvent.getY() <= rectangle.getMaxY()) {
                            panneau.getRectangles().remove(rectangle);
                            panneau.repaint();
                            break;
                        }
                    }
                }
                else {
                    System.out.println("Simple click");
                    ArrayList<Rectangle2D> rectangles = panneau.getRectangles();
                    if (rectangles.isEmpty()) {
                        panneau.addRectangle(mouseEvent.getX(), mouseEvent.getY());
                        panneau.repaint();
                    }
                    else {
                        boolean estDedans = true;
                        for (Rectangle2D rectangle : rectangles) {
                            if (mouseEvent.getX() >= rectangle.getMinX()
                                    && mouseEvent.getX() <= rectangle.getMaxX()
                                    && mouseEvent.getY() >= rectangle.getMinY()
                                    && mouseEvent.getY() <= rectangle.getMaxY()) {
                                estDedans = false;
                            }
                        }

                        if (estDedans) {
                            panneau.addRectangle(mouseEvent.getX(), mouseEvent.getY());
                            panneau.repaint();
                        }
                    }
                }
            }

            @Override
            public void mouseReleased(MouseEvent mouseEvent) {
                super.mouseReleased(mouseEvent);
                panneau.last_dragged = null;
                panneau.last_i = 0;
            }
        });

        fenetre.setContentPane(panneau);
        fenetre.setVisible(true);
    }
}
