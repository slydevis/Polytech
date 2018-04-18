#ifndef __COMPLEXE_H__
#define __COMPLEXE_H__

#include <iostream>

class Complexe {
private:
    float m_reel;
    float m_im;
    float m_module;
    float m_argument;

    void updateGeo();
    void updateAlg();

friend std::ostream& operator<<(std::ostream& os, Complexe c);
friend std::istream& operator>>(std::istream& is, Complexe& c);

public:
    Complexe();
    Complexe(const Complexe &c);
    Complexe(const float a, const float b);
    ~Complexe();

    /*
        Operateur
    */
    Complexe operator+(Complexe c);
    Complexe operator*(const Complexe& c);
    Complexe& operator=(const Complexe c);
    bool operator==(const Complexe c);
    
    /*
        Getters
    */
    float getReel() const;
    float getIm() const;
    float getModule() const;
    float getArgument() const;

    /*
        Setters
    */
    void setReel(const float re);
    void setIm(const float im);
    void setModule(const float mod);
    void setArgument(const float arg);

   void input();
   void display() const;
};

#endif /* __COMPLEXE_H__ */
