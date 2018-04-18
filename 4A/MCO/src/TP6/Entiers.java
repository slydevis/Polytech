package TP6;

/**
 * Entier Permer de gérer une liste de nombre entiers distinct et ordonée
 *
 * @author guillaume
 * @version 1.0
 */
public class Entiers implements MonIterable {
    private int data[];
    private int size = 0;
    private int nbElem = 0;

    public class EntIterator implements BidirIterator, SupIterator {
        private int cur;

        public EntIterator() {
            cur = 0;
        }

        @Override
        public void precedent() {
            --cur;
        }

        @Override
        public void supprime() {
            nbElem--;

            while(cur != nbElem) {
                data[cur] = data[cur + 1];
                cur++;
            }
        }

        @Override
        public int courant() {
            return data[cur];
        }

        @Override
        public void suivant() {
            if(!fin())
                ++cur;
        }

        @Override
        public boolean fin() {
            return cur == size;
        }
    }

    /**
     * Construit une liste d'entrier de taille size
     *
     * @param size taille de la liste
     */
    public Entiers(int size) {
        this.data = new int[size];
        this.size = size;
    }

    /**
     * Insere un nouveau entier dans la liste
     *
     * @param e élément à insérer dans la liste
     */
    public void inserer(int e) {
        if (nbElem < size) {
            int index = 0;

            // Séléction de l'index
            while (index < nbElem) {
                int elem = data[index];
                if (elem < e)
                    index++;
                else if (elem == e) // Element déjà existant on ne l'insere donc pas
                    return;
                else // Element supérieur trouvé on doit donc le mettre à l'index en cours
                    break;
            }

            // Repositionnement des éléments
            for (int i = nbElem - 1; i >= index; --i) {
                data[i + 1] = data[i];
            }

            data[index] = e;
            nbElem++;
        }
        else {
            System.out.println("Hors limite");
            return;
        }
    }

    /**
     * Supprime un entier dans la liste
     *
     * @param e élément à supprimer
     */
    public void supprimer(int e) {
        boolean found = false;
        for (int i = 0; i < nbElem - 1; ++i) {
            if (data[i] == e)
                found = true;

            if (found)
                data[i] = data[i + 1];
        }

        if(!found) {
            System.out.println("Element introuvable");
            return;
        }

        nbElem--;
        data[nbElem] = 0;
    }

    /**
     * Affiche la liste d'entier
     */
    public void afficher() {
        for (int e : data)
            System.out.println(e);
    }

    public void compacter(int n) {
        for(int i = 0; i < n; ++i) {
            supprimer(data[0]);
        }
    }

    public EntIterator createIterator() {
        return new EntIterator();
    }

    public static void main(String[] args) {
        System.out.println("======= ENTIER =======");

        Entiers entier = new Entiers(4);

        System.out.println("======= INITIALISATION =======");

        entier.inserer(4);
        entier.inserer(2);
        entier.inserer(3);
        entier.inserer(5);
        entier.inserer(2);

        entier.afficher();

        System.out.println("======= ITERATOR ======= ");

        EntIterator iterator = entier.createIterator();
        while(!iterator.fin()) {
            System.out.println(iterator.courant());
            iterator.suivant();
        }

        System.out.println("============================== ");

        System.out.println("======= SUPPRESION DU 3 =======");

        entier.supprimer(3);

        entier.afficher();

        System.out.println("======= COMPACTER DE 2 =======");

        entier.compacter(2);

        entier.afficher();

        entier.supprimer(3);
    }
}

