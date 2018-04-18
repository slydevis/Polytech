#ifndef __COMPLEXE_H__
#define __COMPLEXE_H__

#include <iostream>

class Complexe {
private:
	int m_reel;
	int m_im;
	float m_module;
	float m_argument;
	void updateGeo();
	void updateAlg();
friend std::ostream& operator<<(std::ostream& os, Complexe c);
friend std::istream& operator>>(std::istream& is, Complexe& c);
public:
	Complexe();
	Complexe(const Complexe &c);
	Complexe(int a, int b);
	Complexe(float r, float teta);
	~Complexe();
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
};

#endif /* __COMPLEXE_H__ */
