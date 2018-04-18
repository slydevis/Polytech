package TP7;

public interface Adaptateur <E> {
    void push(E e);
    E peek();
    E pop();
}
