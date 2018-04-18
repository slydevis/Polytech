package Casteljau;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.util.ArrayList;

public class CasteljauPanneau extends JPanel {
    public ArrayList<Point> pointControlles;
    public JButton button;

    public CasteljauPanneau() {
        button = new JButton("Reset");
        button.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent mouseEvent) {
                super.mouseClicked(mouseEvent);
                pointControlles.clear();
                repaint();
            }
        });

        add(button);
        pointControlles = new ArrayList<>();
    }

    public void addPoint(Point point) {
        pointControlles.add(point);
    }

    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);

        Graphics2D g = (Graphics2D) graphics;

        // Display point
        for (Point point : pointControlles) {
            Ellipse2D pointDraw = new Ellipse2D.Double(point.x - 5, point.y - 5, 10, 10);
            g.fill(pointDraw);
        }

        g.setColor(Color.BLUE);
        g.setStroke(new BasicStroke(3));

        // Display line
        for (int i = 0; i < pointControlles.size() - 1; ++i) {
            Point beg = pointControlles.get(i);
            Point end = pointControlles.get(i + 1);
            Line2D line = new Line2D.Double(beg.x, beg.y, end.x, end.y);
            g.draw(line);
        }

        if (pointControlles.size() < 2)
            return;

        // Display curve
        ArrayList<Point> points = new ArrayList<>();
        ArrayList<Point> controlles = new ArrayList<>();

        for (double t = 0; t <= 1; t += 0.0001) {
            points = new ArrayList<>();
            points.addAll(pointControlles);

            for (int i = 1; i < pointControlles.size(); ++i) {
                for (int j = 0; j < pointControlles.size() - i; ++j) {
                    Point p1 = points.get((i - 1) + j);
                    Point p2 = points.get((i - 1) + (j + 1));

                    double x = (1.0 - t) * p1.x + t * p2.x;
                    double y = (1.0 - t) * p1.y + t * p2.y;

                    Point point = new Point(x, y);
                    points.set(i + j, point);
                }
            }

            controlles.add(points.get(points.size() - 1));
        }

        g.setColor(Color.RED);

        for (Point point : controlles) {
            g.draw(new Ellipse2D.Double(point.x, point.y, 1, 1));
        }
    }
}
