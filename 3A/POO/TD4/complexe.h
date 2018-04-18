#ifndef __COMPLEXE_H__
#define __COMPLEXE_H__

#include <iostream>
#include "Displayable.h"

class Complexe : public Displayable {
private:
	int m_reel;
	int m_im;
	float m_module;
	float m_argument;
	void updateGeo();
	void updateAlg();
public:
	Complexe();
	Complexe(const Complexe &c);
	Complexe(int a, int b);
	Complexe(float r, float teta);
	virtual ~Complexe();
	Complexe operator+(Complexe c);
	Complexe operator*(const Complexe& c);
	Complexe& operator=(const Complexe c);
	bool operator==(const Complexe c);
	void input();
	void display();
	int getReel() const;
	int getIm() const;
	float getModule() const;
	float getArgument() const;
	void setReel(int re);
	void setIm(int im);
	void setModule(float mod);
	void setArgument(float arg);


	void display(std::ostream& os) const;
};

#endif /* __COMPLEXE_H__ */
