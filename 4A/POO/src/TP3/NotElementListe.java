package TP3;

public class NotElementListe extends ExceptionFaible {
    private int element;

    public NotElementListe(int element) {
        this.element = element;
    }

    @Override
    public String getMessage() {
        return super.getMessage() + "l'élément " + this.element + " est non présent dans la liste";
    }
}
