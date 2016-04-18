#ifndef __DISPLAYABLE_H__
#define __DISPLAYABLE_H__

#include <iostream>

class Displayable {
protected:
	virtual void display(std::ostream& os) const { os << std::endl; }
public:
	friend std::ostream& operator<< (std::ostream& os, const Displayable &obj);
	friend std::ostream& operator<< (std::ostream& os, const Displayable *obj);
};

#endif /* __DISPLAYABLE_H__ */