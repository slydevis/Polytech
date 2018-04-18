package TP7;

public class Renault_clio implements Voiture {
    static double prix = 2000.0;

    @Override
    public double get_prix() {
        return prix;
    }

    public String toString() {
        return "CLIO II";
    }

    public static void main(String[] args) {
        Voiture voiture = new Renault_clio();
        Voiture vUsb = new Lecteur_usb(voiture);
        Voiture vRetro = new Retro_gauche(vUsb);

        System.out.println("La voiture " + vRetro + " à pour prix : " + vRetro.get_prix());
    }
}
