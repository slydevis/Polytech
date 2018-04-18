package TP1;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class PanneauImage extends JPanel {
    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);

        Graphics2D g = (Graphics2D) graphics;

        int x = getWidth() / 4;
        int y = getHeight() / 4;

        String str1 = "Texte 1";
        String str2 = "Texte en ligne";
        String str3 = "Texte à la ligne";

        FontMetrics fontMetrics = g.getFontMetrics();
        int width = fontMetrics.stringWidth(str1);
        int heigth = fontMetrics.getHeight();

        g.drawString(str1, x, y);
        g.drawString(str2, x + width + 3, y);
        g.drawString(str3, x, y + heigth);

        BufferedImage picture = null;
        try {
            picture = ImageIO.read(new File("/home/guillaume/Images/61j4T-iGZYL.png"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        g.drawImage(picture, x, y / 8, 512, 512, null);
    }

    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("Image windows");
        PanneauImage panneauImage = new PanneauImage();
        fenetre.setContentPane(panneauImage);
        fenetre.setVisible(true);
    }
}
