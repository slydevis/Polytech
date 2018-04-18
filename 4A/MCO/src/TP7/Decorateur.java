package TP7;

public class Decorateur implements Voiture {
    private double prix_ajoute;
    private Voiture car;
    private String name;

    public Decorateur(Voiture car, String name, double prix) {
        prix_ajoute = prix;
        this.car = car;
        this.name = name;
    }

    @Override
    public double get_prix() {
        return prix_ajoute + car.get_prix();
    }

    public String toString() {
        return car.toString() + " " + name;
    }
}
