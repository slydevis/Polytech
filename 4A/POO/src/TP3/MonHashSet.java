package TP3;

import TP2.Point;

import java.util.HashSet;

public class MonHashSet<E> extends HashSet<E> {
    public MonHashSet<E> sousEnsembleAleatoire(int n) {
        MonHashSet<E> randomHashSet = new MonHashSet<>();
        RandomHashSetIterator<E> iter = new RandomHashSetIterator<>(this, this.size());

        while (randomHashSet.size() < n)
            randomHashSet.add(iter.next());

        return randomHashSet;
    }

    public static void main(String[] args) {
        HashSet<Point> hashSet = new HashSet<>();
        hashSet.add(new Point(5, 4));
        hashSet.add(new Point(4, 5));
        hashSet.add(new Point(3, 4));
        hashSet.add(new Point(3, 4));

        for (Point point : hashSet)
            System.out.println(point);

        MonHashSet<Point> monHashSet = new MonHashSet<>();
        monHashSet.add(new Point(5, 4));
        monHashSet.add(new Point(4, 5));
        monHashSet.add(new Point(3, 4));
        monHashSet.add(new Point(3, 4));
        monHashSet.add(new Point(6, 7));

        System.out.println("monHashSet = ");
        for (Point point : monHashSet)
            System.out.println(point);

        MonHashSet<Point> alea = monHashSet.sousEnsembleAleatoire(3);

        System.out.println("alea = ");
        for (Point point : alea)
            System.out.println(point);
    }
}
