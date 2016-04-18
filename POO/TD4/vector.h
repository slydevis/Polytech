#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "MesExceptions.h"

class Vector {
protected:
	int* m_data;
private:
	int m_taille;
	int m_nbSet;
	int m_nbGet;
public:
	Vector();
	Vector(const Vector& v);
	virtual ~Vector();
	Vector& operator=(const Vector v);
	int operator[](int i);
	void adjust_size(int i);
	int size() const;
	int get_item(int i) throw(MesExceptions);
	int getNbSet() const;
	int getNbGet() const;
	void set_item(int i, int value);
	void displayInfo() const;
	virtual void display() const;
};

#endif /* __VECTOR_H__ */