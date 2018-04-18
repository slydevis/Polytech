package TP3;

public class PileVide extends ExceptionForte {
    @Override
    public String getMessage() {
        return super.getMessage() + "la pile est vide";
    }
}
