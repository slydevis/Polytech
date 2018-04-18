package TP2;

public class Producteur implements Runnable {
    private BufferCirc buffer;
    private int val;

    public Producteur(BufferCirc b) {
        buffer = b;
    }

    public void run() {
        while(true) {
            buffer.depose(new Integer(val));
            System.out.println(Thread.currentThread().getName() + " a depose " + val);
            val++;
            try {
                Thread.sleep((int) (Math.random()*100));
            }
            catch(InterruptedException e) {}
        }
    }
}
