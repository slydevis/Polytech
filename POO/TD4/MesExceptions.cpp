#include <string>
#include "MesExceptions.h"

using namespace std;

MesExceptions::MesExceptions(const string libelle) : m_libelle(libelle) {

}

const string MesExceptions::getLibelle() const throw() {
	return m_libelle;
}

const char* MesExceptions::what() const throw() {
	return m_libelle.c_str();
}
