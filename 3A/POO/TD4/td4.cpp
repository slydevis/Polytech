#include <iostream>
#include "complexe.h"
#include "vector.h"
#include "PileGen.h"
#include "MesExceptions.h"

using namespace std;

int main() {
	Complexe c(2,3); // 2 + 3i
	cout << c;

	Complexe* cPtr = new Complexe(4,5); // 4 + 5i
	cout << cPtr;

	delete cPtr;

	Vector tab;
	tab.adjust_size(4);
	tab.set_item(0, 1);
	tab.set_item(1, 2);
	tab.set_item(2, 3);
	tab.set_item(3, 4);
	// tab.set_item(4, 5); Lance une exception
	
	PileGen<int> pile("The pile");

	try {
		// cout << tab[99] << endl;
		// tab.set_item(99, 0); // Lance une exception
		// cout << pile.getFirstElement() << endl; // Lance une exception
		pile.display(); // Lance une exception
	} 
	catch(MesExceptions& e) {
		cout << "Erreur : " << e.what() << endl;
	} 
	catch(...) {
		cout << "Une erreur non attendu est survenu" << endl;
	}
	return 0;
}