package TP1;

public class Noeud {
    protected int val;
    protected Noeud fd = null;
    protected Noeud fg = null;

    public Noeud() {
        this.val = 0;
    }

    public Noeud(int val) {
        this.val = val;
    }
}

