package TP3;

public class HorsLimites extends ExceptionForte {
    private int index;

    public HorsLimites(int index) {
        this.index = index;
    }

    @Override
    public String getMessage() {
        return super.getMessage() + "Hors limite (index = " + this.index + ")";
    }
}
