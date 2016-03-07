#include <iostream>
#include <bitset>

#define TAB_SIZE 64

using namespace std;

// Initialise le tableau (mise a zero)
void init(unsigned long int &x) {
    x = x&0;
}

// assigne a vrai le bit en position pos
void setTrue(unsigned long int &x, int pos) {
    if(pos > TAB_SIZE)
        return;
        
    unsigned long int tmp = 1;
    for(unsigned i = 0; i < pos; ++i)
        tmp <<= 1;
                
    x = x|tmp;
}

// assigne a faux le bit en position pos
void setFalse(unsigned long int &x, int pos) {
    if(pos > TAB_SIZE)
        return;
        
    unsigned long int tmp = 1;
    for(unsigned i = 0; i < pos; ++i)
        tmp <<= 1;
           
    tmp = ~tmp;
    x = x&tmp; 
}

// retourne la valeur du bit en position pos
bool get(unsigned long int &x, int pos) {
    if(pos > TAB_SIZE)
        return false;
    
    unsigned long int tmp = x;
    for(unsigned i = 0; i < pos; ++i)
        tmp >>= 1;
        
    return tmp;
}

int main() {
    cout << sizeof(unsigned long int)*8 << endl; // Renvoi 64 
    unsigned long int x;
    
    init(x);
    setTrue(x, 3);
    setTrue(x, 4);
    setFalse(x, 4);

    bitset<64> xBinary(x);
    cout << "x = " << xBinary << endl;
    
    cout << "x(3) = " << get(x, 3) << endl;
    setTrue(x, 5);
    cout << "x(5) = " << get(x, 5) << endl;
    setFalse(x, 8);
    cout << "x(8) = " << get(x, 8) << endl;
 
    return 0;
}
