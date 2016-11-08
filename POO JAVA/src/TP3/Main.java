package TP3;

import TP1.Piles;
import TP2.Point;

import java.io.File;
import java.io.IOException;
import java.util.*;

public class Main {
    public static void main(String[] argv) {
        try {
            Piles pile = new Piles(9);
            pile.empiler(4); // A commenter pour générer une exeption PileVide
            pile.depiler();
        } catch (PileVide pileVide) {
            pileVide.printStackTrace();
        }

        /********** TABLEAU ASSOCIATIVES ************/
        File f = new File(System.getProperty("user.dir") + "\\src\\TP3\\test.txt");
        TreeMap<String, Integer> treeMap = new TreeMap<>();

        Scanner scanner = null;

        try {
            scanner = new Scanner(f);
        } catch (IOException e) {
            e.printStackTrace();
        }

        /* Initialisation du tableau avec le fichier */
        if(scanner != null) {
            while(scanner.hasNext()) {
                String word = scanner.next().toLowerCase();
                int nbOccur = (treeMap.containsKey(word) ? treeMap.get(word) + 1 : 1);
                treeMap.put(word, nbOccur);
            }
            scanner.close();
        }

        /* Récupération de la sous table < au milieu */
        TreeMap<String, Integer> infMilieu = new TreeMap<>();
        /* Récupération de la sous table où 3 <= occur <= 5 */
        TreeMap<String, Integer> occurEntre3et5 = new TreeMap<>();

        for(Map.Entry<String,Integer> entry : treeMap.entrySet()) {
            String key = entry.getKey();
            Integer occur = entry.getValue();

            if(occur >= 3 && occur <= 5)
                occurEntre3et5.put(key, occur);
            if(key.compareTo("milieu") < 0)
                infMilieu.put(key, occur);
        }

        /* On affiche le résultat */
        System.out.println("Doublets dont le mot est inférieur à \"milieu\"");
        for(Map.Entry<String, Integer> entry : infMilieu.entrySet())
            System.out.println("map[" + entry.getKey() + "] = " + entry.getValue());

        System.out.println("Doublets dont le nombre d'occurences est compris entre 3 et 5");
        for(Map.Entry<String, Integer> entry : occurEntre3et5.entrySet())
            System.out.println("map[" + entry.getKey() + "] = " + entry.getValue());

        /********** ENSEMBLES ************/
        HashSet<Point> hashSet = new HashSet<>();
        hashSet.add(new Point(5, 4));
        hashSet.add(new Point(4, 5));
        hashSet.add(new Point(3, 4));
        hashSet.add(new Point(3, 4));
        Iterator<Point> it = hashSet.iterator();
        while (it.hasNext()) {
            System.out.println(it.next());
        }

        MonHashSet<Point> monHashSet = new MonHashSet<>();
        monHashSet.add(new Point(3,4));
        monHashSet.add(new Point(4,5));
        monHashSet.add(new Point(5,4));

        MonHashSet<Point> sousEnsemble = monHashSet.sousEnsembleAléatoire(3);
        it = sousEnsemble.iterator();
        while(it.hasNext())
            System.out.println(it.next());

        /********* ITERATEURS **********/
        ArrayList<Integer> arrayList = new ArrayList<>();
        LinkedList<Integer> integerLinkedList = new LinkedList<>();
        ListIterator<Integer> iter;

        Random rn = new Random();

        for (int i = 0; i<= 1000000 ; i++)
            arrayList.add(rn.nextInt(999));

        long debut = System.currentTimeMillis();

        for (int i = 0; i <= 100000; i++)
            arrayList.add(500000, rn.nextInt(999));

        System.out.println((System.currentTimeMillis()-debut)/100/60 +" minute" + " et "+ (System.currentTimeMillis()-debut)/100.0%60 +"secondes");
        System.out.println("fini ArrayList");


        for (int i = 0; i<= 1000000 ; i++)
            integerLinkedList.add(rn.nextInt(999));

        iter = integerLinkedList.listIterator(500000);
        debut = System.currentTimeMillis();

        for (int i = 0; i <= 100000; i++)
            iter.add(rn.nextInt(999));

        System.out.println((System.currentTimeMillis()-debut)/100/60 +" minute" + " et "+ (System.currentTimeMillis()-debut)/100.0%60 +"secondes");
        System.out.println("fini LinkedList");
    }
}
