package TP3;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Random;

public class IterateursMain {
    public void formatTime(double time) {
        double elepsedTime = System.currentTimeMillis() - time;
        double minutes = Math.round((elepsedTime / 100) / 60);
        double secondes = Math.round((elepsedTime / 100) % 60);

        System.out.println(minutes + " minute" + " et " + secondes + " secondes" + " et " + elepsedTime + " ms");
    }

    public static void main(String[] args) {
        IterateursMain iterateursMain = new IterateursMain();

        ArrayList<Integer> arrayList = new ArrayList<>();
        LinkedList<Integer> linkedList = new LinkedList<>();
        ListIterator<Integer> listIterator;

        Random random = new Random();

        for (int i = 0; i < 1000000; ++i) {
            arrayList.add(random.nextInt());
            linkedList.add(random.nextInt());
        }

        System.out.println("DEBUT TEST ArrayList");

        long debut = System.currentTimeMillis();

        for (int i = 0; i < 100000; ++i)
            arrayList.add(arrayList.size() / 2, random.nextInt());

        iterateursMain.formatTime(debut);

        System.out.println("FIN TEST ArrayList");

        debut = System.currentTimeMillis();

        listIterator = linkedList.listIterator(linkedList.size() / 2);

        System.out.println("DEBUT TEST ArrayList");

        for (int i = 0; i < 100000; ++i)
            listIterator.add(random.nextInt());

        iterateursMain.formatTime(debut);

        System.out.println("FIN TEST LinkedList");
    }
}
