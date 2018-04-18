package TP2;

import TP4.MyInfo;

@MyInfo(annee = 1994)
public class Point {
    private int x;
    private int y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Point() {
        this(0, 0);
    }

    public int getX() {
        return this.x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return this.y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public String toString() {
        return "(" + x + ", " + y + ")";
    }

    public Point additionner(Point p) {
        return new Point(x + p.getX(), y + p.getY());
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (o == null || getClass() != o.getClass())
            return false;

        Point point = (Point) o;

        return x == point.x && y == point.y;
    }

    @Override
    public int hashCode() {
        return x + y;
    }

    public static void main(String[] args) {
        System.out.println("Test de la classe Point");
        Point point = new Point(1, 1);
        Point point1 = new Point();

        System.out.println("Point 1 = " + point);
        System.out.println("Point 2 = " + point1);

        if (point.equals(point))
            System.out.println("Point 1 == Point 1");

        if (!point.equals(point1))
            System.out.println("Les deux points sont différents");

        point1 = point1.additionner(point);

        System.out.println("Point 2 = " + point1);

        Point point3 = new Point();
        point3.setX(1);
        point3.setY(1);

        System.out.println("Point 3 = " + point3);

        if (point.equals(point3))
            System.out.println("Les deux points sont bien égaux");

        Segment segment = new Segment(new Point(1, 1), new Point(3, 3));

        if (!point.equals(segment))
            System.out.println("Point 1 != Segment");
    }
}
