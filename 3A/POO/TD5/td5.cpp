#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <stack>

using namespace std;
using namespace rel_ops;

class TestClass {
public:
	unsigned lenght;
	bool operator==(const TestClass& t) const {
		return this->lenght == t.lenght;
	}
	bool operator<(const TestClass& t) const {
		return this->lenght < t.lenght;
	}
};

int main() {

/************************************************ 
		Partie I : Opérateurs de comparaison           
*************************************************/ 

	TestClass a, b;
	a.lenght = 0;
	b.lenght = 0;

	if(a == b)
		cout << "a == b" << endl;
	else
		cout << "a != b" << endl;

	b.lenght++;

	if(a != b)
		cout << "a != b" << endl;
	else
		cout << "a == b" << endl;

	if(a < b)
		cout << "a < b" << endl;
	else
		cout << "a > b" << endl;

	// ça marche !!!
	if(b > a)
		cout << "b > a" << endl;
	else
		cout << "b < a" << endl;


/************************************************ 
			Partie II : Classe string                
*************************************************/

	string str = "une string quoi";
	cout << "Chaine de caractere de taille " << str.size() << " = " << str << endl;

/************************************************ 
			Partie III : Vector et List               
*************************************************/

	vector<int> vec;
	vector<int>::iterator it;

	for(unsigned i = 0; i < 10; ++i)
		vec.push_back(i + 100);

	// On affiche le vecteur a l'aide d'iterator
	for(it = vec.begin(); it != vec.end(); ++it)
		cout << *it << endl;
	
	list<int> l;
	list<int>::iterator itl;
	for(unsigned i = 0; i < 10; ++i)
		l.push_back(i + 200);

	// On affiche la liste a l'aide d'iterator
	for(itl = l.begin(); itl != l.end(); ++itl)
		cout << *itl << endl;

/************************************************ 
				Partie IV : Pile
*************************************************/ 
	stack<int> pile;
	for(unsigned i = 0; i < 10; ++i)
		pile.push(i + 300);

	for(unsigned i = 0; pile.size(); ++i) {
		cout << pile.top() << endl;
		pile.pop();		
	}

	cout << "Apres affichage pile.size() = " << pile.size() << endl;

	return 0;
}