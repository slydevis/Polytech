#include <iostream>
#include "vector.h"
#include "vector15.h"

using namespace std;

namespace {
	// Il faut un peu de polymorphisme parceque c'est cool
	void checkDisplayVirtual(Vector* v) {
		v->display();
	}

	void partie2() {
		Vector tab;
		cout << "Agrandissement du tableau à 4" << endl;
		tab.adjust_size(4);
		tab.set_item(0, 1);
		tab.set_item(1, 2);
		tab.set_item(2, 3);
		tab.set_item(3, 4);
		tab.set_item(4, 5);

		cout << "Affichage des éléments" << endl;
		for(unsigned i = 0; i < tab.size() + 1; ++i)
			cout << "tab[" << i << "] = " << tab.get_item(i) << endl;

		cout << "Diminution du tableau à 2" << endl;
		tab.adjust_size(2);
		for(unsigned i = 0; i < tab.size(); ++i)
			cout << "tab[" << i << "] = " << tab.get_item(i) << endl;

		cout << "Test de l'operateur []" << endl;
		for(unsigned i = 0; i < tab.size(); ++i)
			cout << "tab[" << i << "] = " << tab[i] << endl;

		cout << "Test creation par copie" << endl;
		Vector copie(tab);
		for(unsigned i = 0; i < copie.size(); ++i)
			cout << "copie[" << i << "] = " << copie[i] << endl;

		cout << "Test de l'operateur = " << endl;
		Vector egal;
		egal = copie;
		for(unsigned i = 0; i < egal.size(); ++i)
			cout << "egal[" << i << "] = " << egal[i] << endl;	


		cout << endl << "Même test mais pour Vector15" << endl << endl;

		Vector15 tab15;
		cout << "Agrandissement du tableau à 4" << endl;
		// tab15.adjust_size(4); // Problème
		for(unsigned i = 0; i < tab15.size(); ++i)
			tab15.set_item(i, i+1);

		cout << "Affichage des éléments" << endl;
		for(unsigned i = 0; i < tab15.size() + 1; ++i)
			cout << "tab15[" << i << "] = " << tab15.get_item(i) << endl;

		cout << "Test de l'operateur []" << endl;
		for(unsigned i = 0; i < tab15.size(); ++i)
			cout << "tab15[" << i << "] = " << tab15[i] << endl;

		cout << "Test creation par copie" << endl;
		Vector15 copie15(tab15);
		for(unsigned i = 0; i < copie15.size(); ++i)
			cout << "copie15[" << i << "] = " << copie15[i] << endl;

		cout << "Test de l'operateur = " << endl;
		Vector egal15;
		egal15 = copie15;
		for(unsigned i = 0; i < egal15.size(); ++i)
			cout << "egal15[" << i << "] = " << egal15[i] << endl;	


		cout << "Test fonction display : " << endl;
		cout << "Sur un type Vector :" << endl;
		checkDisplayVirtual(&tab);
		cout << "Sur un type Vector15 : " << endl;
		checkDisplayVirtual(&tab15);
	}
}

int main() {
	partie2();
	return 0;
}