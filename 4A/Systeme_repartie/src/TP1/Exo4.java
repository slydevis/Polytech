package TP1;

import java.util.Random;

public class Exo4 implements Runnable {
    @Override
    public void run() {
        Random random = new Random();
        for(int i = 0; i  < 10; ++i) {
            try {
                int time = Math.abs(random.nextInt()%200);
                Thread.sleep(time);
                System.out.println(Thread.currentThread().getName());
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Exo4 tache = new Exo4();

        Thread thread1 = new Thread(tache);
        thread1.setName("Tache 1");
        thread1.start();

        Thread thread2 = new Thread(tache);
        thread2.setName("Tache 2");
        thread2.start();

        Thread thread3 = new Thread(tache);
        thread3.setName("Tache 3");
        thread3.start();

        thread1.join();
        thread2.join();
        thread3.join();

        System.out.println("Fin du Main thread");
    }
}
