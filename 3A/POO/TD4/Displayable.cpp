#include "Displayable.h"

std::ostream& operator<< (std::ostream& os, const Displayable &obj) {
	obj.display(os);
	return os;
}

std::ostream& operator<< (std::ostream& os, const Displayable *obj) {
	obj->display(os);
	return os;
}