#ifndef __MESEXCEPTIONS_H__
#define __MESEXCEPTIONS_H__

#include <iostream>
#include <string>
#include <exception>

using namespace std;

class MesExceptions : public exception {
private:
	string m_libelle;
public:
	MesExceptions(const string libelle);
	virtual ~MesExceptions() throw() {}
	virtual const string getLibelle() const throw();
 	virtual const char* what() const throw();
};

#endif /* __MESEXCEPTIONS_H__ */