#include <iostream>
#include "PileGen.h"

using namespace std;

int main() {
	// Testé avec des int, float, string
	PileGen<string> pile("Tab");
	cout << pile.getName() << endl;
	pile.push("0.0f");
	pile.push("1.1f");
	pile.push("2.2f");
	pile.push("3.3f");
	pile.display();

	cout << pile << endl;
	cout << "Premier element = " << pile.getFirstElement() << endl;
	
	pile.pop();
	pile.display();

	pile.pop();	
	pile.pop();
	pile.pop();
	pile.pop();
	if(pile.isempty())
		cout << "OK" << endl;
	else
		cout << "Pas OK" << endl;

	cout << "Premier element = " << pile.getFirstElement() << endl;

	cout << "FIN" << endl;
	return 0;
}