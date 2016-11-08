package TP4;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Scanner;

@My_Info(annee = 2005)
public class Main {
    public static void main(String[] args) {
        System.out.println("Entrez le nom du classe à utilisé : ");
        Scanner input = new Scanner(System.in);
        String class_name = input.next();

        System.out.println("Classe name = " + class_name);

        Field[] tf;
        Method[] me;

        try {
            Class<?> my_class = Class.forName(class_name);

            tf = my_class.getDeclaredFields();
            me = my_class.getDeclaredMethods();

            System.out.println("Attributs");

            for (Field f: tf)
                System.out.println(f);

            System.out.println("\n");
            System.out.println("Methodes");

            for (Method m : me)
                System.out.println(m);

            System.out.println("\n");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        input.close();
    }
}
