package TP3;

import java.io.File;
import java.io.IOException;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class MainTreeMap {
    public static void main(String[] args) {

        try {
            File f = new File(System.getProperty("user.dir") + "/src/TP3/test.txt");
            Scanner sc = new Scanner(f);
            TreeMap<String, Integer> treeMap = new TreeMap<>();

            while (sc.hasNext()) {
                String word = sc.next().toLowerCase();
                int nbOccur = (treeMap.containsKey(word) ? treeMap.get(word) + 1 : 1);
                treeMap.put(word, nbOccur);
            }

            sc.close();

            /* Récupération de la sous table < au milieu */
            TreeMap<String, Integer> infMilieu = new TreeMap<>();

            /* Récupération de la sous table où 3 <= occur <= 5 */
            TreeMap<String, Integer> occurEntre3et5 = new TreeMap<>();

            for (Map.Entry<String, Integer> entry : treeMap.entrySet()) {
                String key = entry.getKey();
                Integer occur = entry.getValue();

                if (occur >= 3 && occur <= 5)
                    occurEntre3et5.put(key, occur);
                if (key.compareTo("milieu") < 0)
                    infMilieu.put(key, occur);
            }

            /* On affiche le résultat */
            System.out.println("Doublets dont le mot est inférieur à \"milieu\"");
            for (Map.Entry<String, Integer> entry : infMilieu.entrySet())
                System.out.println("map[" + entry.getKey() + "] = " + entry.getValue());

            System.out.println("Doublets dont le nombre d'occurences est compris entre 3 et 5");
            for (Map.Entry<String, Integer> entry : occurEntre3et5.entrySet())
                System.out.println("map[" + entry.getKey() + "] = " + entry.getValue());

        } catch (IOException e) {
            System.out.println("Erreur");
        }
    }
}
