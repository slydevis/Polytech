#include <iostream>
#include <math.h>
#include "complexe.h"

using namespace std;

/*

2ème étape 
Dans un deuxième temps et dans cet ordre : 
on fera en sorte que r et teta soit valorisés 
on redéfinira l'opérateur << et l'opérateur >> 
on redéfinira l'opérateur ==  

*/

/*
	Constructors 
*/

Complexe::Complexe() {
	cout << endl << "Construction d'un complexe par défault" << endl;
	m_reel = 0;
	m_im = 0;
	updateGeo();
}

Complexe::Complexe(const Complexe &c) {
	cout << endl << "Construction d'un complexe par recopie" << endl;
	m_reel = c.getReel();
	m_im = c.getIm();
	m_argument = c.getArgument();
	m_module = c.getModule();
}

Complexe::Complexe(int a, int b) {
	cout << endl << "Construction d'un complexe par rapport a la notation algebrique" << endl;
	m_reel = a;
	m_im = b;
	updateGeo();
}

Complexe::Complexe(float r, float teta) {
	cout << endl << "Construction d'un complexe par rapport a la notation geometrique" << endl;
	m_module = r;
	m_argument = teta;
	updateAlg();
}

/*
	Destructor
*/

Complexe::~Complexe() {
	cout << endl << "Destruction d'un complexe : " << m_reel << " + " << m_im << "i " << endl;
}

void Complexe::updateAlg() {
	m_reel = m_module * cos(m_argument);
	m_im = m_module * sin(m_argument);
	cout << "m_argument = " << m_argument << endl;
}

void Complexe::updateGeo() {
	// TODO : Je pense que c'est faux
	m_module = sqrt(m_reel*m_reel+m_im*m_im);
	m_argument = atan2(m_reel, m_reel);
}

Complexe Complexe::operator+(const Complexe c) {
	Complexe cTmp;
	cTmp.setReel(m_reel + c.getReel());
	cTmp.setIm(m_im + c.getIm());
	return cTmp;
}

Complexe Complexe::operator*(const Complexe& c) {
	cout << "Je veux mettre l'arguement = " << m_argument + c.getArgument() << endl;
	Complexe cTmp;
	cTmp.setModule(m_module * c.getModule());
	cTmp.setArgument(m_argument + c.getArgument());
	return cTmp;
}

Complexe& Complexe::operator=(const Complexe c) {
	if(&c == this)
		return *this;

	m_reel = c.getReel();
	m_im = c.getIm();
	m_argument = c.getArgument();
	m_module = c.getModule();

	return *this;
}

bool Complexe::operator==(const Complexe c) {
	if(m_reel != c.getReel())
		return false;
	if(m_im != c.getIm())
		return false;
	if(m_module != c.getModule())
		return false;
	if(m_argument != c.getArgument())
		return false;
	return true;
}

void Complexe::display(ostream& os) const {
	os << "Complexe : \n";
	os << "Notation algebrique : " << getReel();
	(getIm() > 0 ? os << "+" << getIm() : os << "-" << getIm());
	os << "i\n";
	os << "Notation geometrique : " << getModule() << "(cos(" << getArgument() << ") + isin(" << getArgument() << ")\n"; 
}

/*stream& operator>>(istream& is, Complexe& c) {
	int reel, im;
	cout << "Reel = ";
	is >> reel;
	cout << endl << "Imaginaire = ";
	is >> im;
	c.setReel(reel);
	c.setIm(im);
	return is;
}
*/
void Complexe::input() {
	cout << "Entrer a : ";
	cin >> m_reel;
	cout << "Entrer ib : ";
	cin >> m_im;
	updateGeo();
}

void Complexe::display() {
	cout << "Complexe : " << endl;
	cout << "Notation algebrique : " << m_reel;
	(m_im > 0 ? cout << "+" << m_im : cout << "-" << m_im);
	cout << 'i' << endl;
	cout << "Notation geometrique : " << m_module << "(cos(" << m_argument << ") + isin(" << m_argument << ")" << endl; 
}

int Complexe::getReel() const {
	return m_reel;
}

int Complexe::getIm() const {
	return m_im;
}

float Complexe::getModule() const {
	return m_module;
}

float Complexe::getArgument() const {
	return m_argument;
}

void Complexe::setReel(int re) {
	m_reel = re;
	updateGeo();
}

void Complexe::setIm(int im) {
	m_im = im;
	updateGeo();
}

void Complexe::setModule(float mod) {
	m_module = mod;
	updateAlg();
}

void Complexe::setArgument(float arg) {
	m_argument = arg;
	updateAlg();
}