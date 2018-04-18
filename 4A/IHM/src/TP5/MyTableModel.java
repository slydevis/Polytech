package TP5;

import TP1.Fenetre;

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.TableModel;

public class MyTableModel extends AbstractTableModel {
    private int rowNumber;
    private int columnNumber;

    public MyTableModel(int row, int column) {
        this.rowNumber = row;
        this.columnNumber = column;
    }

    @Override
    public int getRowCount() {
        return rowNumber;
    }

    @Override
    public int getColumnCount() {
        return columnNumber;
    }

    @Override
    public Object getValueAt(int row, int column) {
        int speed = 8 + row * 2;

        if (column == 0) {
            return speed + " km/h";
        }

        int distance = (column * 60 * 5);
        return distance / speed;
    }

    public String getColumnName(int index) {
        if (index == 0)
            return "";
        else
            return index * 5 + " km";
    }

    public static void main(String[] args) {
        Fenetre fenetre = new Fenetre("CadreTable", 800, 200);

        TableModel tableModel = new MyTableModel(8, 10);

        JTable table = new JTable(tableModel);

        JScrollPane scrollPane = new JScrollPane(table, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);

        fenetre.add(scrollPane);
        fenetre.setVisible(true);
    }
}
