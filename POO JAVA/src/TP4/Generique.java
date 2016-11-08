package TP4;

import TP1.ArbreBinaire;

public class Generique<A> {
    private A info1;
    private A info2;

    public Generique(A a, A b) {
        info1 = a;
        info2 = b;
    }

    public A getInfo1() {
        return info1;
    }

    public A getInfo2() {
        return info2;
    }

    public void setInfo1(A v1) {
        info1 = v1;
    }

    public void setInfo2(A v2) {
        info2 = v2;
    }

    public Generique<A> fusionner(Generique<A> g) {
        return new Generique<A>(getInfo1(), g.getInfo2());
    }

    public static void main(String[] args) {
        Article a1 = new Article(10, 20.0, 9);
        Article a2 = new Article(11, 23.0, 42);

        ElectroMenager e1 = new ElectroMenager(88, 52.0, 9);
        ElectroMenager e2 = new ElectroMenager(99, 54.0, 32);

        System.out.println("a1 = { " + a1 + " }");
        System.out.println("a2 = { " + a2 + " }");
        System.out.println("e1 = { " + e1 + " }");
        System.out.println("e2 = { " + e2 + " }");

        // Generique<ElectroMenager> g2 = new Generique<>(e1, e2);
        Generique<Article> g2 = new Generique<>(e1, e2);
        Generique<Article> g1 = new Generique<>(a1, a2);

        // g1.fusionner(g2);
        // Marche pas car g2 et un Generique<ElectroMenager> (sans correction)
        g1.fusionner(g2);

        // Generique<Article> ga = new Generique<ElectroMenager>(e1, e2);
        // Marche pas car il veux cast en ElectroMenager
        Generique<Article> ga = new Generique<>(e1, e2);
        ga.setInfo1(a1);
        ga.setInfo1(e1);
        ga.setInfo1(ga.getInfo1());

        Generique<? super ElectroMenager> ge = new Generique<ElectroMenager>(e1, e2);
        ge.setInfo1(e1);
        // Le compilateur ne connais pas le type exact du parametre donc ça marche pas
        // ge.setInfo1(a1);
        // ge.setInfo1(ge.getInfo1());
        ge.setInfo1(e1);
    }
}
