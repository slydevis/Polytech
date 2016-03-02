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
    unsigned long int tmp = 1;
    for(int i = 0; i < pos; ++i)
        tmp <<= 1;        
    x = x|tmp;
}

// assigne a faux le bit en position pos
void setFalse(unsigned long int &x, int pos) {

}

// retourne la valeur du bit en position pos
bool get(unsigned long int &x, int pos);

int main() {
    cout << sizeof(unsigned long int)*8 << endl; // Renvoi 64 
    unsigned long int x;
    
    init(x);
    setTrue(x, 3);
    setTrue(x, 4);
    setFalse(x, 4);

    bitset<64> xBinary(x);
    cout << "x = " << xBinary << endl;
    
    return 0;
}
