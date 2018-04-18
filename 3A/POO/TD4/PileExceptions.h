#ifndef __PILEEXCEPTIONS_H__
#define __PILEEXCEPTIONS_H__

#include "MesExceptions.h"

class PileExceptions : public MesExceptions {
public:
	PileExceptions(string libelle);
	virtual ~PileExceptions() throw();
	virtual const char* what() const throw();
};

#endif /* __PILEEXCEPTIONS_H__ */