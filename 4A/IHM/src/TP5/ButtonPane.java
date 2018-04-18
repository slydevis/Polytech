package TP5;

import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreePath;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ButtonPane extends JPanel {
    private JButton buttonAdd;
    private JButton buttonDel;

    public ButtonPane(TreePane treePane) {
        buttonAdd = new JButton("AJOUT");
        buttonDel = new JButton("SUPPRIMER");

        buttonAdd.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                DefaultTreeModel model = (DefaultTreeModel) treePane.getTree().getModel();
                DefaultMutableTreeNode lastNode = (DefaultMutableTreeNode) treePane.getTree().getLastSelectedPathComponent();
                DefaultMutableTreeNode node = new DefaultMutableTreeNode("New Node");
                model.insertNodeInto(node, lastNode, 0);
                treePane.getTree().scrollPathToVisible(new TreePath(node.getPath()));
            }
        });

        buttonDel.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                DefaultTreeModel model = (DefaultTreeModel) treePane.getTree().getModel();
                TreePath[] paths = treePane.getTree().getSelectionPaths();

                if(paths != null) {
                    DefaultMutableTreeNode node;

                    for (TreePath path : paths) {
                        node = (DefaultMutableTreeNode) path.getLastPathComponent();

                        if (!node.isRoot())
                            model.removeNodeFromParent(node);
                    }
                }
            }
        });

        add(buttonAdd);
        add(buttonDel);
    }
}
