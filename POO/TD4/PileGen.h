#ifndef __PILEGEN_H__
#define __PILEGEN_H__

#include <iostream>
#include "CNode.h"

using namespace std;

template <typename T>
class PileGen {
private:
	CNode<T>* m_head;
	string m_name;
	unsigned m_size;
	template <typename U> friend ostream& operator<<(ostream &os, PileGen<U> pile);
public:
	PileGen(string name);
	~PileGen();
	void push(T elem);
	T pop();
	bool isempty() const;
	string getName() const;
	T getFirstElement() const;
	virtual void display(ostream& os = cout);
};

#include "PileGen.hxx" // A cause de l'édition de lien et le template

#endif /* __PILEGEN_H__ */	