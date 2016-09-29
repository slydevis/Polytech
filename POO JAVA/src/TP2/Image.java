package TP2;

public class Image extends Forme {
    private final int MAX_ITEMS = 100;
    private Forme[] formesCollec;
    private Point pOrigin;
    private int nbFormes;

    public Image() {
        formesCollec = new Forme[MAX_ITEMS];
        nbFormes = 0;
        pOrigin = new Point();
    }

    public Image(Point p) {
        this(); // On utilise le constructeur par défault
        pOrigin = p;
    }

    public void ajouter(Forme f) {
        formesCollec[nbFormes] = f;
        nbFormes++;
    }

    @Override
    public void dessiner(Piletransformations pt) {
        System.out.println("Image :");
        System.out.println("pOrigin :" + pOrigin.additionner(pt.getCourant()));

        for(int i = 0; i < nbFormes; ++i) {
        	Forme f = formesCollec[i];
            f.dessiner(pt);
        }
    }

    @Override
    public void deplacer(Point p) {
        pOrigin = pOrigin.additionner(p);
    }
}
