#ifndef __VECTOREXCEPTION_H__
#define __VECTOREXCEPTION_H__

#include "MesExceptions.h"
#include "vector.h"

class VectorException : public MesExceptions {
private:
	int m_pos;
	int m_size;
public:
	VectorException(string libelle, int pos, Vector *v) : MesExceptions(libelle), m_pos(pos), m_size(v->size()) {}
	virtual ~VectorException() throw() {}
	virtual const char* what() const throw();
};

#endif /* __VECTOREXCEPTION_H__ */