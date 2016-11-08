package TP3;

public class NotElementEntiers extends ExceptionFaible {
    int element;
    public NotElementEntiers(int element) {
        this.element = element;
    }

    @Override
    public String getMessage() {
        return super.getMessage() + "l'entier " + element + " est non présent dans la liste d'entier";
    }
}
