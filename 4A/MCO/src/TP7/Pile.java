package TP7;

import java.util.ArrayList;

public class Pile<E> extends ArrayList<E> implements Adaptateur<E> {
    @Override
    public void push(E e) {
        add(0, e);
    }

    @Override
    public E peek() {
        return get(0);
    }

    @Override
    public E pop() {
        E tmp = get(0);
        remove(0);
        return tmp;
    }

    public static void main(String[] args) {
        Pile<Integer> p = new Pile<>();

        p.push(1);
        p.push(4);
        p.push(8);

        for (int i = 0; i < 3; i++) {
            System.out.println(p.peek());
            System.out.println(p.pop());
        }
    }
}
