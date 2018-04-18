package TP1;

import java.util.ArrayList;

public class Exo5 implements Runnable {
    private double i;
    private double end;

    private static double N = 10.0;
    private static double n = 1000.0;

    private static ArrayList<Double> results = new ArrayList<>();
    private static ArrayList<Thread> threads = new ArrayList<>();

    private Exo5(double k) {
        i = 1.0 + ((k - 1.0) * (n / N));
        this.end = k * (n / N);
    }

    @Override
    public void run() {
        double result = 0.0;

        for (; i <= end; ++i) {
            double tmp = i - 1.0 / 2.0;
            tmp = tmp / n;
            tmp = tmp * tmp;
            tmp = 1.0 + tmp;
            tmp = 4.0 / tmp;
            result += 1.0 / n * tmp;
        }

        results.add(result);
    }

    public static void main(String[] args) throws InterruptedException {
        for (double k = 1.0; k <= N; ++k) {
            Exo5 task = new Exo5(k);
            Thread thread = new Thread(task);
            thread.start();
            threads.add(thread);
        }

        for (Thread thread : threads) {
            thread.join();
        }

        double resultFinal = 0.0;
        for (double result : results) {
            resultFinal += result;
        }

        System.out.println("RESULT = " + resultFinal);
    }
}
