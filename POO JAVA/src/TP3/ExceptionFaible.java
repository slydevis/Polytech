package TP3;

public class ExceptionFaible extends Exception {
    @Override
    public String getMessage() {
        return "Exception faible : ";
    }
}
