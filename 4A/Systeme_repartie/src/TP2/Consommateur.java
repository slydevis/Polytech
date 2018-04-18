package TP2;

public class Consommateur implements Runnable {
    private BufferCirc buffer;

    public Consommateur(BufferCirc b) {
        buffer = b;
    }

    public void run() {
        Integer val;
        while(true) {
            val = (Integer) buffer.preleve();
            System.out.println(Thread.currentThread().getName() + " a preleve " + val);
            try {
                Thread.sleep((int)(Math.random()*300));
            }
            catch(InterruptedException e) {}
        }
    }
}
