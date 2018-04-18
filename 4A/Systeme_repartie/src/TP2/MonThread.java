package TP2;

public class MonThread extends Thread {
    private MonObjet obj1, obj2;

    public MonThread(MonObjet o1, MonObjet o2) {
        obj1 = o1;
        obj2 = o2;
    }

    public void run() {
        obj1.action1(obj2);
    }
}
