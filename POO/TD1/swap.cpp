#include "swap.h"

void swap(int &a, int &b) {
		int tmp = a;
		a = b;
		b = tmp;
}

void swapSansRef(int a, int b) {
	int tmp = a;
	a = b;
	b = tmp;
}

/*

Le compilateur rale car on souhaite modifie des parametres constantes

*/

/*

inline void swapConst(const int a, const int b) {
	int tmp = a;
	a = b;
	b = tmp;
}

*/