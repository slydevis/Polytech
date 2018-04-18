#include <iostream>
#include "swap.h"
#include "complexe.h"

using namespace std;

void partie1() {
    int a, b;
    cout << "Entrer a : ";
    cin >> a;
    cout << "Entrer b : ";
    cin >> b;

    swapSansRef(a, b);                                                                                                  // Marche pas car on travaille sur des copies des variables
    cout << endl << "swapSansRef(a,b) : a = " << a << " b = " << b << endl;
    // swapConst(a, b);                                                                                                   // Marche à cause des consts
    // cout << endl << "swapConst(a,b) : a = " << a << " b = " << b << endl;
    swapInline(a, b);                                                                                                       // Marche pas car on travaille sur des copies des variables
    cout << endl << "swapInline(a,b) : a = " << a << " b = " << b << endl;
    swap(a,b);                                                                                                                  // Tous va bien
    cout << endl << "swap(a,b) : a = " << a << " b = " << b << endl;
}

void partie2() {
    Complexe c;
    c.setReel(3);
    c.setIm(4);
    c.display();

    cout << "Creation d'un deuxieme complexe par recopie : " << endl;
    Complexe c2(c);
    c2.display();

    cout << "Cration d'un troisieme complexe par parametre par defaut" << endl;
    Complexe c3(3, 4);
    c3.display();

    cout << "addition 3 + 4i + 3 + 4i = 6 + 8i " << endl;
    c3 = c3 + c2;
    c3.display();
    cout << "Multiplication " << endl;
    c3 = c * c;
    c3.display();

    cout << "Test de l'input" << endl;
    c3.input();
    c3.display();

    cout << "Test des operateur de flux :" << endl;
    cout << "Test de l'operateur << " << endl;
    cout << c3 << endl;
    cout << "Test de l'operateur >>" << endl;
    cin >> c3;
    cout << c3;

    cout << "Test de l'operateur == " << endl;
    if(c == c2)
        cout << "C == C2 (OK)" << endl;
    else
        cout << "C != C2" << endl;
    if(c == c3)
        cout << "C == C3" << endl;
    else
        cout << "C != C3 (OK)" << endl; 
}

int main() {
    partie1();
    partie2();
    return 0;
}