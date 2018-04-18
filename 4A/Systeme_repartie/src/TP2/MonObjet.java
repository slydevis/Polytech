package TP2;

public class MonObjet {
    public MonObjet() {

    }

    public synchronized void action1(MonObjet o) {
        try {
            Thread.currentThread().sleep(200);
        } catch (InterruptedException ex) {
            return;
        }

        o.action1(this);
    }

    public synchronized void action2(MonObjet o) {
        try {
            Thread.currentThread().sleep(200);
        } catch (InterruptedException ex) {
            return;
        }

        o.action2(this);
    }
}
