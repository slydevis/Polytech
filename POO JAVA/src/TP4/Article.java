package TP4;

public class Article {
    private long code;
    private Double prixHT;
    private int quantite;

    public Double prixTTC() {
        Double p;
        p=1.196*prixHT;
        return p;
    }

    public void retirer(int x) {
        quantite = quantite - x ;
    }

    public void ajouter(int x) {
        quantite = quantite + x;
    }

    public Article(long c, Double prix, int q) {
        code = c;
        prixHT = prix;
        quantite = q;
    }

    public String toString(){
        return "code = " + code +"; prix = " + prixHT + "; quantite = " + quantite;
    }
}
