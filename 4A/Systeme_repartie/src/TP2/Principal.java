package TP2;

public class Principal {
    public static void main(String[] args) {
        int t = 20;
        int p = 2;
        int c = 2;

        BufferCirc b = new BufferCirc(t);

        for(int i = 0; i < p; ++i) {
            Producteur producteur = new Producteur(b);
            Thread P1 = new Thread(producteur);
            P1.setName("P" + i);
            P1.start();
        }

        for(int i = 0; i < c; ++i) {
            Consommateur consommateur = new Consommateur(b);
            Thread C1 = new Thread(consommateur);
            C1.setName("C" + i);
            C1.start();
        }
    }
}
