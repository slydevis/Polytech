package TP2;

public class Task implements Runnable {
    MonSemaphore semaphore;

    public Task() {
        semaphore = new MonSemaphore(2, "Task");
    }

    @Override
    public void run() {
        System.out.println("Je démarre");
        try {
            semaphore.P();
            System.out.println("Je bloque");
            Thread.sleep(2000);
            semaphore.V();
            System.out.println("Je fini");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
