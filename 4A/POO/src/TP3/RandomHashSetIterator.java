package TP3;

import java.util.*;

public class RandomHashSetIterator<E> implements Iterator<E> {
    private Vector<Integer> alreadyUse;
    private HashSet<E> hashSet;
    private final int end;
    private Random random;

    public RandomHashSetIterator(HashSet<E> hashSet, int end) {
        this.alreadyUse = new Vector<>();
        this.end = end;
        this.hashSet = hashSet;
        this.random = new Random();
    }

    public boolean hasNext() {
        return this.alreadyUse.size() < end;
    }

    private int selectIndex() {
        return random.nextInt(hashSet.size());
    }

    public E next() {
        if (hasNext()) {
            int i = 0;
            int selectedElement = selectIndex();

            Iterator<E> it = hashSet.iterator();

            while (it.hasNext()) {
                if (i == selectedElement) {
                    if (alreadyUse.contains(i)) {
                        return next();
                    }
                    else {
                        alreadyUse.addElement(i);
                        E elem = it.next();
                        System.out.println(elem);
                        return elem;
                    }
                }

                ++i;
                it.next();
            }
        }
        else {
            throw new NoSuchElementException();
        }

        return null;
    }
}
