package TP5;

import TP1.Fenetre;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;

public class FormeListRenderer extends JPanel implements ListCellRenderer {
    private String cellName;
    private Shape shape;

    static final String[] listStr = {"Carre", "Cercle", "Segment"};

    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);

        Graphics2D g = (Graphics2D) graphics;

        FontMetrics metrics = graphics.getFontMetrics();
        int width = metrics.stringWidth(cellName);
        int heigth = metrics.getHeight();
        g.drawString(cellName, 0, heigth);

        width = width + 10;

        if (cellName.equals("Carre")) {
            shape = new Rectangle2D.Double(width, 0, heigth - 1, heigth - 1);
        }
        else if (cellName.equals("Cercle")) {
            shape = new Ellipse2D.Double(width, 0, heigth - 1, heigth - 1);
        }
        else if (cellName.equals("Segment")) {
            shape = new Line2D.Double(width, 0, width + heigth - 5, heigth);
        }

        g.draw(shape);
    }

    @Override
    public Component getListCellRendererComponent(JList jList, Object o, int i, boolean selected, boolean focused) {
        cellName = (String) o;

        Color background;
        Color foreground;

        if (selected) {
            background = jList.getSelectionBackground();
            foreground = jList.getSelectionForeground();
        }
        else {
            background = jList.getBackground();
            foreground = jList.getForeground();
        }

        setBackground(background);
        setForeground(foreground);

        return this;
    }

    @Override
    public Dimension getPreferredSize() {
        Graphics g = this.getGraphics();

        this.paintComponent(g);

        FontMetrics fontMetrics = g.getFontMetrics();
        int width = fontMetrics.stringWidth(cellName);
        int height = Math.max(fontMetrics.getHeight(), shape.getBounds().height);

        return new Dimension(width + shape.getBounds().width + 10, height + 5);
    }

    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("CadreList", 150, 100);
        fenetre.setLayout(new FlowLayout());

        JList list = new JList(FormeListRenderer.listStr);
        list.setCellRenderer(new FormeListRenderer());
        fenetre.add(list);
        fenetre.setVisible(true);
    }
}
