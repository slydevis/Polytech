package TP5;

import TP1.Fenetre;

import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import java.awt.*;

public class TreePane extends JPanel {
    private JTree tree;

    public TreePane() {
        DefaultMutableTreeNode root = new DefaultMutableTreeNode("Root");

        tree = new JTree(root);
        tree.setEditable(true);

        DefaultMutableTreeNode node1 = new DefaultMutableTreeNode("Node 1");
        DefaultMutableTreeNode node11 = new DefaultMutableTreeNode("Node 1-1");
        DefaultMutableTreeNode node12 = new DefaultMutableTreeNode("Node 1-2");
        DefaultMutableTreeNode node13 = new DefaultMutableTreeNode("Node 1-3");
        node1.add(node11);
        node1.add(node12);
        node1.add(node13);

        root.add(node1);

        DefaultMutableTreeNode node2 = new DefaultMutableTreeNode("Node 2");
        DefaultMutableTreeNode node21 = new DefaultMutableTreeNode("Node 2-1");
        DefaultMutableTreeNode node22 = new DefaultMutableTreeNode("Node 2-2");
        DefaultMutableTreeNode node23 = new DefaultMutableTreeNode("Node 2-3");
        node2.add(node21);
        node2.add(node22);
        node2.add(node23);

        root.add(node2);

        add(tree);
    }

    public JTree getTree() {
        return this.tree;
    }

    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("JTree");

        TreePane treePane = new TreePane();
        ButtonPane buttonPane = new ButtonPane(treePane);

        fenetre.add(new JScrollPane(treePane.tree), BorderLayout.CENTER);
        fenetre.add(buttonPane, BorderLayout.SOUTH);

        fenetre.setVisible(true);
    }
}
