package TP7;

import java.util.Observable;

public class Point extends Observable implements Cloneable {
    public int x ;
    public int y ;

    public Point() {
        x = 0 ;
        y = 0 ;
    }

    public Point(int a, int b) {
        x = a ;
        y = b ;
    }

    public void modifier(int a, int b) {
        x = a;
        y = b;

        setChanged();
        notifyObservers();
    }

    public String toString() {
        return  "("+x+","+y+")" ;
    }

    public Point clone(){
        return new Point(x, y);
    }
}
