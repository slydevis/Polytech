#include <string.h>
#include "PileExceptions.h"
#include "MesExceptions.h"
PileExceptions::PileExceptions(string libelle) : MesExceptions(libelle) {}

PileExceptions::~PileExceptions() throw() {}

const char* PileExceptions::what() const throw() {
	string result = "Pile Exception : ";
	result = result + MesExceptions::what();
	return result.c_str();
}