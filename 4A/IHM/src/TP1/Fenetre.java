package TP1;

import javax.swing.*;
import java.awt.*;

public class Fenetre extends JFrame {
    public Fenetre(String name) {
        setTitle(name);

        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension dimension = toolkit.getScreenSize();
        setSize((int) (dimension.getWidth() / 2), (int) (dimension.getHeight() / 2));
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    public Fenetre(String name, int width, int height) {
        this(name);
        setSize(width, height);
    }

    public Fenetre(String name, int width, int height, int x, int y) {
        this(name, width, height);
        setBounds(x, y, width, height);
    }

    public static void main(String[] args) throws InterruptedException {
        Fenetre fenetre1 = new Fenetre("First Windows", 400, 100, 0, 0);
        Thread.sleep(2000);

        Fenetre fenetre2 = new Fenetre("Second Windows");
        Thread.sleep(2000);

        fenetre1.setExtendedState(Frame.MAXIMIZED_BOTH);
        Thread.sleep(2000);

        fenetre1.toFront();
        fenetre1.setResizable(false);
    }
}
