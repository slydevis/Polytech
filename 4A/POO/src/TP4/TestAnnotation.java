package TP4;

import java.io.File;

public class TestAnnotation {
    public static void main(String[] args) {
        File f = new File(System.getProperty("user.dir") + "/src/TP2/");
        String[] ts = f.list();

        for (String name : ts) {
            // On retire le .java à la fin du fichier
            name = name.substring(0, name.length() - 5);
            name = "TP2.".concat(name);

            try {
                Class<?> c = Class.forName(name);

                if (!c.isAnnotationPresent(MyInfo.class))
                    System.out.println("Classe " + name + " n'a pas d'annotation");
                else {
                    MyInfo info = c.getAnnotation(MyInfo.class);
                    if (info.annee() >= 2009)
                        System.out.println("name = " + name + "; annee = " + info.annee());
                }
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
    }
}
