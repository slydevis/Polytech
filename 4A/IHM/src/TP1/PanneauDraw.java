package TP1;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class PanneauDraw extends JPanel {
    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);

        Graphics2D g = (Graphics2D) graphics;

        int x = getWidth() / 4;
        int y = getHeight() / 4;

        Rectangle2D rectangle = new Rectangle.Double(x, y, x * 2, y * 2);

        Ellipse2D ellipse = new Ellipse2D.Double();
        ellipse.setFrame(rectangle);

        Line2D diagonale = new Line2D.Double(rectangle.getX(), rectangle.getY(), rectangle.getMaxX(), rectangle.getMaxY());

        Ellipse2D circle = new Ellipse2D.Double();
        circle.setFrameFromCenter(rectangle.getCenterX(), rectangle.getCenterY(), rectangle.getCenterX() + 100.0, rectangle.getCenterY() + 100.0);

        g.draw(rectangle);
        AffineTransform trans_rectangle = new AffineTransform();
        trans_rectangle.rotate(Math.PI / 4, rectangle.getCenterX(), rectangle.getCenterY());
        g.setStroke(new BasicStroke(10));
        g.draw(trans_rectangle.createTransformedShape(rectangle));
        g.setStroke(new BasicStroke());

        g.setColor(new Color(255, 0, 0, 155));
        g.setPaint(new GradientPaint(new Point2D.Double(ellipse.getMinX(), ellipse.getMinY()),
                Color.RED,
                new Point2D.Double(ellipse.getMaxX(),
                        ellipse.getMaxY()), Color.YELLOW));

        BufferedImage picture = null;
        try {
            picture = ImageIO.read(new File("/home/guillaume/Images/2017-03-18-06-27-36.jpg"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        g.setPaint(new TexturePaint(picture, new Rectangle2D.Double(0, 0, 100, 100)));

        g.fill(ellipse);

        g.setColor(Color.BLUE);
        g.draw(diagonale);

        g.setColor(Color.GREEN);
        g.draw(circle);

        AffineTransform trans_circle = new AffineTransform();
        trans_circle.translate(50, 100);
        g.setStroke(new BasicStroke(10));
        g.draw(trans_circle.createTransformedShape(circle));
        g.setStroke(new BasicStroke());

        g.setColor(Color.BLACK);
        g.drawString("HELLO", (int) rectangle.getCenterX(), (int) rectangle.getCenterY());
    }

    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("Draw Window");
        PanneauDraw panneauDraw = new PanneauDraw();
        fenetre.setContentPane(panneauDraw);
        fenetre.setVisible(true);
    }
}
