package TP3;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;

public class PanneauDessin extends JPanel {
    private Color color;
    private Ellipse2D cercle;
    private Rectangle2D rectangle;
    private String shapename;
    private Dimension dimension;

    public PanneauDessin() {

    }

    public void setCouleur(Color color) {
        this.color = color;
    }

    public void setForme(String shapename) {
        this.shapename = shapename;
    }

    public void setDimension(Dimension dimension) {
        this.dimension = dimension;
    }

    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);

        Graphics2D g = (Graphics2D) graphics;

        if(color != null) {
            g.setColor(color);

            if(shapename != null) {
                if(dimension != null) {
                    if(shapename.equals("cercle")) {
                        cercle = new Ellipse2D.Double(0, 0, dimension.width, dimension.width);
                        g.fill(cercle);
                    }
                    else if(shapename.equals("rectangle")) {
                        rectangle = new Rectangle2D.Double(0, 0, dimension.width, dimension.height);
                        g.fill(rectangle);
                    }
                }
            }
        }
    }

}
