package TP3;

public class NotElementListe extends ExceptionFaible {
    int entier;
    
    public NotElementListe(int entier) {
        this.entier = entier;
    }

    @Override
    public String getMessage() {
        return super.getMessage() + "L'élément " + entier + " est non présente dans la liste";
    }
}
