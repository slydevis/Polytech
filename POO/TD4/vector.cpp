#include <iostream>
#include "MesExceptions.h"
#include "VectorException.h"
#include "vector.h"

using namespace std;

Vector::Vector() {
	m_taille = 0;
	m_nbGet = 0;
	m_nbSet = 0;
	m_data = new int[m_taille];
}

Vector::Vector(const Vector& v) {
	m_taille = v.size();
	m_nbSet = v.getNbSet();
	m_nbGet = v.getNbGet();
	m_data = new int[m_taille];

	for(unsigned i = 0; i < m_taille; ++i)
		m_data[i] = v.m_data[i];
}

Vector::~Vector() {
	delete[] m_data;
}

Vector& Vector::operator=(const Vector v) {
	if(&v == this)
		return *this;

	m_taille = v.size();
	m_nbGet = v.getNbGet();
	m_nbSet = v.getNbSet();
	m_data = new int[m_taille];
	for(unsigned i = 0; i < m_taille; ++i)
		m_data[i] = v.m_data[i];

	return *this;
}

int Vector::operator[](int i) {
	return get_item(i);
}

void Vector::adjust_size(int size) {
	if(size == m_taille)
		return;
	if(size < 0)
		throw VectorException("dans adjust_size", size, this);

	// Sauvegarde des données
	int tab[m_taille];
	for(unsigned i = 0; i < m_taille; ++i)
		tab[i] = m_data[i];

	m_taille = size;
	delete[] m_data;
	m_data = new int[m_taille];

	// Restitution des données (partiel dans le cas d'une reduction de tableau)
	for(unsigned i = 0; i < m_taille; ++i)
		m_data[i] = tab[i];
}

int Vector::size() const {
	return m_taille;
}

int Vector::get_item(int i) throw(MesExceptions) {
	if(i > m_taille-1) 
		throw VectorException("dans get_item", i, this);
	
	m_nbGet++;
	return m_data[i];
}

void Vector::set_item(int i, int value) {
	if(i > m_taille-1)
		throw VectorException("dans set_item", i, this);

	m_data[i] = value;
	m_nbSet++;
}

int Vector::getNbSet() const {
	return m_nbSet;
}

int Vector::getNbGet() const {
	return m_nbGet;
}

void Vector::displayInfo() const {
	cout << "Nb Get = " << m_nbGet << "; Nb Set = " << m_nbSet << endl;
}

void Vector::display() const {
	cout << "display() de la classe Vector" << endl;

	for(unsigned i = 0; i < m_taille; ++i)
		cout << "tab[" << i << "] = " << m_data[i] << endl;
}