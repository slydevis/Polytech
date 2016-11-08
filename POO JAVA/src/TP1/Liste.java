package TP1;

import TP2.Structure;

public class Liste extends Structure implements Cloneable {
    private Maillon list;

    private class Maillon {
        private int value;
        private Maillon next;

        private Maillon(int value, Maillon next) {
            this.value = value;
            this.next = next;
        }

        private void afficher() {
            if(next != null) {
                System.out.print(value + " -> ");
                next.afficher();
            }
            else {
                System.out.println(value);
            }
        }
    }

    public Liste() {
        this.list = null;
    }

    /**
     * @param first premier élément de la liste
     */
    public Liste(Maillon first) {
        this.list = first;
    }

    /**
     * @param e entier à chercher dans la liste
     * @return vrai si l'entier est présent dans la liste
     */
    private boolean estPresent(int e) {
        Maillon cur = list;

        while(cur != null) {
            if(cur.value == e)
                return true;
            cur = cur.next;
        }

        return false;
    }

    /**
     * @param e nouvelle élément à inserer dans la liste
     */
    @Override
    public void inserer(int e) {
        if(!estPresent(e)) {
            Maillon newMaillon = new Maillon(e, list);
            list = newMaillon;
        }
    }

    /**
     * @param e élément à supprimer de la liste
     */
    @Override
    public void supprimer(int e) {
        if(estPresent(e)) {
            Maillon mail = list;

            // Si la liste contiens qu'un élément
            if (mail != null && mail.next == null) {
                if(mail.value == e) {
                    list = null;
                    return;
                }
            }

            // Si l'élément est le premier élément de la liste
            if (mail != null && mail.next != null) {
                if (mail.value == e) {
                    list = mail.next;
                    return;
                }
            }

            while (mail != null) {
                if(mail.next != null && mail.next.value == e) {
                    mail.next = mail.next.next;
                    return;
                }
                mail = mail.next;
            }
        }
    }

    @Override
    public void afficher() {
        list.afficher();
    }

    @Override
    public void compacter(int nb) {
        for(int i = 0; i < nb; ++i)
            supprimer(i);
    }

    public Liste clone() throws CloneNotSupportedException {
        return (Liste) super.clone();
    }

    public static void main(String[] args) {
        Liste liste = new Liste();
        liste.inserer(3);
        liste.inserer(6);
        liste.inserer(4);
        liste.inserer(3);
        liste.inserer(1);
        liste.afficher();
        liste.supprimer(4);
        liste.afficher();
    }
}