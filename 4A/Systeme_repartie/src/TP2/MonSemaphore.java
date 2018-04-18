package TP2;

public class MonSemaphore {
    private int n;
    String name;

    public MonSemaphore(int max, String o) {
        n = max;
        name = o;
    }

    synchronized public void P() {
        while(n == 0) {
            try {
                this.wait();
            } catch (InterruptedException ex) {

            }
        }

        n--;
    }

    synchronized public void V() {
        n++;
        this.notify();
    }

    public static void main(String[] args) throws InterruptedException {
        Task task = new Task();

        Thread thread1 = new Thread(task);
        Thread thread2 = new Thread(task);
        Thread thread3 = new Thread(task);
        Thread thread4 = new Thread(task);

        thread1.start();
        thread2.start();
        thread3.start();
        thread4.start();

        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
    }
}
