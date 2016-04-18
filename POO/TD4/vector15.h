#ifndef __VECTOR15_H__
#define __VECTOR15_H__

#include "vector.h"

class Vector15 : public Vector {
private:
	void adjust_size(int i);
public:
	Vector15();
	Vector15(const Vector15& v);
	virtual ~Vector15();
	void display() const;
};

#endif /* __VECTOR15_H__ */