package TP2;

public abstract class Forme {
	private Point pOrigin;
	
	public Forme() {
		pOrigin = new Point();
	}
	
	public Forme(Point po) {
		pOrigin = po;
	}
	
	public Point getOrigin() { return this.pOrigin; }
    public abstract void dessiner(Piletransformations pt);
    public void deplacer(Point p) {
    	pOrigin = pOrigin.additionner(p);
    }
}
