package TP2;

public class Deadlock {
    public static void main(String[] args) {
        MonObjet o1 = new MonObjet();
        MonObjet o2 = new MonObjet();

        MonThread t1 = new MonThread(o1, o2);
        t1.setName("t1");
        MonThread t2 = new MonThread(o2, o1);
        t2.setName("t2");
        t1.start();
        t2.start();
    }
}
