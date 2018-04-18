#include <iostream>
using namespace std;

template <typename T>
CNode<T>::CNode(T data, CNode<T>* ptr) : m_data(data), m_next(ptr) {}

template <typename T>
CNode<T>::~CNode() {
	cout << "Destruction d'un CNode" << endl;
	delete m_next;
}

template <typename T>
T CNode<T>::getData() const {
	return m_data;
}

template <typename T>
CNode<T>* CNode<T>::getNext() const {
	return m_next;
}

template <typename T>
void CNode<T>::setData(T data) {
	m_data = data;
}

template <typename T>
void CNode<T>::setNext(CNode<T>* next) {
	m_next = next;
}