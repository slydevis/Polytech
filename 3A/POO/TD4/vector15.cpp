#include <iostream>
#include "vector15.h"

using namespace std;
Vector15::Vector15() : Vector() {
	Vector::adjust_size(15);
}

Vector15::Vector15(const Vector15& v) : Vector(v) {
	Vector::adjust_size(15);
}

Vector15::~Vector15() {

}

void Vector15::display() const {
	cout << "display() de la classe Vector15" << endl;

	for(unsigned i = 0; i < size(); ++i)
		cout << "tab[" << i << "] = " << m_data[i] << endl;
}