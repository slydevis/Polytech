package TP4;

import TP1.Entier;
import TP2.Point;
import TP3.HorsLimites;
import TP3.NotElementEntiers;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.Scanner;

public class Introspection {
    public void a() {
        // Question A
        System.out.println("====== QUESTION A ======");
        System.out.println("Entrer le nom de la classe à utilisé : ");
        Scanner input = new Scanner(System.in);
        String className = input.next();

        System.out.println("Class name = " + className);

        Field fields[];
        Method methods[];

        try {
            Class<?> c = Class.forName(className);

            fields = c.getFields();
            methods = c.getMethods();

            System.out.println("Attributs :");
            for (Field f : fields)
                System.out.println(f);

            System.out.println("Methodes :");
            for (Method m : methods)
                System.out.println(m);

        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void b() {
        System.out.println("====== QUESTION B ======");
        Scanner scanner = new Scanner(System.in);
        System.out.println("Entier de quelle taille ?");
        Entier entier = new Entier(scanner.nextInt());
        String message;

        do {
            System.out.println("Quelle action (INSERER, SUPPRIMER, AFFICHER, QUIT) ?");
            message = scanner.next().toUpperCase();

            if (message.matches("INSERER") || message.matches("SUPPRIMER")) {
                System.out.println("Quelle valeur ?");
                int value = scanner.nextInt();
                switch (message) {
                    case "INSERER":
                        try {
                            entier.inserer(value);
                        } catch (HorsLimites horsLimites) {
                            horsLimites.printStackTrace();
                        }
                        break;
                    case "SUPPRIMER":
                        try {
                            entier.supprimer(value);
                        } catch (NotElementEntiers notElementEntiers) {
                            notElementEntiers.printStackTrace();
                        }
                        break;
                }
            }
            else if (message.matches("AFFICHER")) {
                entier.afficher();
            }
        } while (!message.matches("QUIT"));
    }

    public void c() {
        Point point = new Point(3, 4);
        Scanner scanner = new Scanner(System.in);

        Field[] fields = point.getClass().getFields();
        System.out.println(Arrays.toString(fields));
    }

    public void d() {

    }

    public static void main(String[] args) {
        Introspection introspection = new Introspection();
        Scanner s = new Scanner(System.in);

        System.out.println("Entrer la lettre de l'exercice :");
        switch (s.next().toUpperCase().charAt(0)) {
            case 'A':
                introspection.a();
                break;
            case 'B':
                introspection.b();
                break;
            case 'C':
                introspection.c();
                break;
            case 'D':
                introspection.d();
                break;
            default:
                break;
        }
    }
}
