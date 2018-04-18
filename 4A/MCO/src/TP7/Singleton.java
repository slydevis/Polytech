package TP7;

public class Singleton {
    private static Singleton instance = null;

    private Singleton() {
    }

    public static Singleton getInstance() {
        if(Singleton.instance == null)
            Singleton.instance = new Singleton();

        return Singleton.instance;
    }

    public static void main(String[] args) {
        Singleton singleton = Singleton.getInstance();
    }
}
