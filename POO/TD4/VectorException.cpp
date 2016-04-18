#include <sstream>
#include "VectorException.h"

const char* VectorException::what() const throw() {
	ostringstream ostr;
	ostr << MesExceptions::what() << " : acces a la position " << m_pos;
	ostr << " alors que la taille est = " << m_size << endl;	
	return ostr.str().c_str();
}
