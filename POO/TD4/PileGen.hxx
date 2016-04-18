#include <iostream>
#include "MesExceptions.h"
#include "PileExceptions.h"
using namespace std;

template <typename T> 
PileGen<T>::PileGen(string name) {
	m_name = name;
	m_size = 0;
	m_head = NULL;
}

template <typename T>
PileGen<T>::~PileGen() {
	cout << "Destruction d'un PileGen" << endl;
}

template <typename T>
void PileGen<T>::display(ostream& os) {
	if(isempty())
		return;

	CNode<T>* headTmp = m_head;
	while(headTmp->getNext() != NULL) {
		os << headTmp->getData() << " ";
		headTmp = headTmp->getNext();
	}

	os << headTmp->getData();
	os << endl;
}

template <typename T>
string PileGen<T>::getName() const {
	return m_name;
}

template <typename T>
void PileGen<T>::push(T elem) {
	m_head = new CNode<T>(elem, m_head);
	m_size++;
}

template <typename T>
T PileGen<T>::pop() {
	if(!isempty()) {
		CNode<T>* tmp = m_head;
		m_head = m_head->getNext();
		if(m_size > 0)
			m_size--;
		tmp->setNext(NULL);
		delete tmp; 
	}

	if(!isempty())
		return m_head->getData();
	else
		return T();
}

template <typename T>
bool PileGen<T>::isempty() const {
	return (m_head == NULL);
}

template <typename T>
T PileGen<T>::getFirstElement() const {
	if(!isempty())
		return m_head->getData();

	cout << "La pile est vide" << endl;
	return T();
}

template <typename T>
ostream& operator<< (ostream& os, PileGen<T> pile) {
	os << "Nom de la pile = " << pile.getName() << endl;
	os << "Donnée de la pile : ";
	pile.display(os);
	return os;
}