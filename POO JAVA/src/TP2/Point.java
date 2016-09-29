package TP2;

public class Point {
    private int x;
    private int y;

    public Point() {
        x = 0;
        y = 0;
    }

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public Point additionner(Point p) {
    	return new Point(x + p.getX(), y + p.getY());
    }

    public String toString() {
        return "(" + x + ", " + y + ")";
    }
}
