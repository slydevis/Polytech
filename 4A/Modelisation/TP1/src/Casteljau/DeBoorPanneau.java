package Casteljau;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.util.ArrayList;

public class DeBoorPanneau extends JPanel {
    private ArrayList<Double> knotVector;
    private ArrayList<Point> controlPoints;
    private int k = 3;

    private JButton resetButton;
    private JLabel label;
    private JTextField degField;

    public DeBoorPanneau() {
        knotVector = new ArrayList<>();
        controlPoints = new ArrayList<>();

        resetButton = new JButton("Reset");
        resetButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent mouseEvent) {
                super.mouseClicked(mouseEvent);
                controlPoints.clear();
                repaint();
            }
        });

        add(resetButton);

        label = new JLabel("Degre :");
        add(label);

        degField = new JTextField(10);
        degField.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent documentEvent) {
                changeK();
            }

            @Override
            public void removeUpdate(DocumentEvent documentEvent) {
                changeK();
            }

            @Override
            public void changedUpdate(DocumentEvent documentEvent) {
                changeK();
            }

            public void changeK() {
                if(!degField.getText().isEmpty()) {
                    int val = Integer.parseInt(degField.getText());
                    if(val >= 2) {
                        k = Integer.parseInt(degField.getText());
                        repaint();
                    }
                }
            }
        });
        add(degField);
    }

    public void addPoint(Point point) {
        controlPoints.add(point);
    }

    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);
        Graphics2D g = (Graphics2D) graphics;

        // Display control point
        for (Point point : controlPoints) {
            Ellipse2D pointDraw = new Ellipse2D.Double(point.x - 5, point.y - 5, 10, 10);
            g.fill(pointDraw);
        }

        g.setColor(Color.BLUE);
        g.setStroke(new BasicStroke(3));

        // Display line
        for (int i = 0; i < controlPoints.size() - 1; ++i) {
            Point beg = controlPoints.get(i);
            Point end = controlPoints.get(i + 1);
            Line2D line = new Line2D.Double(beg.x, beg.y, end.x, end.y);
            g.draw(line);
        }

        // De Boor
        knotVector.clear();

        for (int i = 0; i <= k - 1; i++) {
            knotVector.add(0.0);
        }

        for (int i = k; i < controlPoints.size(); i++) {
            knotVector.add((double) (i + 1 - k));
        }

        for (int i = controlPoints.size(); i <= controlPoints.size() - 1 + k; i++) {
            knotVector.add((double) (controlPoints.size() + 1 - k));
        }

        if (controlPoints.size() < 2)
            return;

        // Display curve
        ArrayList<Point> printedPoints = new ArrayList<>();
        for (double t = 0.0001; t < controlPoints.size() + 1 - k; t += 0.0001) {
            printedPoints.add(DeBoor(t));
        }

        g.setColor(Color.RED);
        for (Point point : printedPoints) {
            g.draw(new Ellipse2D.Double(point.x, point.y, 1, 1));
        }
    }

    private Point DeBoor(Double t) {
        int i = 0;
        while (!(knotVector.get(i) <= t) || !(knotVector.get(i + 1) >= t)) {
            i++;
        }

        ArrayList<Double> N = new ArrayList<>();
        N.add(0, 0.0);
        N.add(1, 1.0);
        N.add(2, 0.0);
        for (int j = 0; j <= k - 2; ++j) {
            N.add(0.0);
        }

        ArrayList<Double> Ncpy = new ArrayList<>();
        for (int p = 2; p <= k; ++p) {
            Ncpy.clear();
            Ncpy.addAll(N);

            double tmp_1;
            double tmp_2;

            for (int j = 1; j <= p + 1; j++) {
                if (Ncpy.get(j - 1) > 0.0) {
                    tmp_1 = (t - knotVector.get(j + i - p)) * Ncpy.get(j - 1) / (knotVector.get(j + i - 1) - knotVector.get(j + i - p));
                }
                else {
                    tmp_1 = 0.0;
                }

                if (Ncpy.get(j) > 0.0) {
                    tmp_2 = (knotVector.get(j + i) - t) * Ncpy.get(j) / (knotVector.get(j + i) - knotVector.get(j + i - p + 1));
                }
                else {
                    tmp_2 = 0.0;
                }

                N.set(j, tmp_1 + tmp_2);
            }
        }

        double x = 0.0;
        double y = 0.0;
        for (int j = 1; j <= k && j > 0; ++j) {
            x += controlPoints.get(i - k + j).x * N.get(j);
            y += controlPoints.get(i - k + j).y * N.get(j);
        }

        return new Point(x, y);
    }
}

