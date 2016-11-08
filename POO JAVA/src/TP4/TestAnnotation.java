package TP4;

import java.io.File;

public class TestAnnotation {
    public static void main(String[] args) {
        // Affichage des classes crée avant 2009
        File f = new File(System.getProperty("user.dir") + "\\\\src\\\\TP4\\");
        String[] ts = f.list();

        for(String name : ts){
            name = name.substring(0, name.length() - 5);
            name = "TP4.".concat(name);

            try {
                Class<?> c = Class.forName(name);
                System.out.println("classe : " + name);

                if (!c.isAnnotationPresent(My_Info.class))
                    System.out.println("pas d'annotation");

                if (c.isAnnotationPresent(My_Info.class)){
                    System.out.println("il y a des annotation  ");

                    My_Info info = c.getAnnotation(My_Info.class);

                    if (info.annee() >= 2009)
                        System.out.println(info);
                }
            } catch (ClassNotFoundException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            System.out.println("\n");
        }
    }
}
