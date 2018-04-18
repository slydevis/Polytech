#include <iostream>
#include <math.h>
#include "complexe.h"

using namespace std;

/*
    Constructeurs 
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

Complexe::Complexe(const float a, const float b) {
    cout << endl << "Construction d'un complexe par rapport a la notation algebrique" << endl;
    m_reel = a;
    m_im = b;
    updateGeo();
}

/*
    Destructor
*/

Complexe::~Complexe() {
    cout << endl << "Destruction d'un complexe : " << m_reel << " + " << m_im << "i " << endl;
}

void Complexe::updateAlg() {
    m_reel = m_module * cosf(m_argument);
    m_im = m_module * sinf(m_argument);
 }

void Complexe::updateGeo() {
    m_module = sqrtf(m_reel*m_reel+m_im*m_im);
    m_argument = atanf(m_im/m_reel);
}

/*
    Operateur
*/
Complexe Complexe::operator+(const Complexe c) {
    Complexe cTmp;
    cTmp.setReel(m_reel + c.getReel());
    cTmp.setIm(m_im + c.getIm());
    return cTmp;
}

Complexe Complexe::operator*(const Complexe& c) {
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

ostream& operator<<(ostream& os, Complexe c) {
    os << "Complexe : \n";
    os << "Notation algebrique : " << c.getReel();
    (c.getIm() > 0 ? os << "+" << c.getIm() : os << "-" << c.getIm());
    os << "i\n";
    os << "Notation geometrique : " << c.getModule() << "(cos(" << c.getArgument() << ") + isin(" << c.getArgument() << ")\n"; 
    return os;
}

istream& operator>>(istream& is, Complexe& c) {
    int reel, im;
    cout << "Reel = ";
    is >> reel;
    cout << endl << "Imaginaire = ";
    is >> im;
    c.setReel(reel);
    c.setIm(im);
    return is;
}

/*
    Getters
*/
float Complexe::getReel() const {
    return m_reel;
}

float Complexe::getIm() const {
    return m_im;
}

float Complexe::getModule() const {
    return m_module;
}

float Complexe::getArgument() const {
    return m_argument;
}

/*
    Setters
*/
void Complexe::setReel(const float re) {
    m_reel = re;
    updateGeo();
}

void Complexe::setIm(const float im) {
    m_im = im;
    updateGeo();
}

void Complexe::setModule(const float mod) {
    m_module = mod;
    updateAlg();
}

void Complexe::setArgument(const float arg) {
    m_argument = arg;
    updateAlg();
}

void Complexe::input() {
    cout << "Entrer a : ";
    cin >> m_reel;
    cout << "Entrer ib : ";
    cin >> m_im;
    updateGeo();
}

void Complexe::display() const{
    cout << "Complexe : " << endl;
    cout << "Notation algebrique : " << m_reel;
    (m_im > 0 ? cout << "+" << m_im : cout << "-" << m_im);
    cout << 'i' << endl;
    cout << "Notation geometrique : " << m_module << "(cos(" << m_argument << ") + isin(" << m_argument << ")" << endl; 
}
