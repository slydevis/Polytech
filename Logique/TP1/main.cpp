#include <iostream>
#include <time.h>
#include <stdlib.h>

#define NB_VALUE (1<<28)

using namespace std;

int main() {
    srand(time(NULL));
    
    unsigned int *tab = new unsigned int[NB_VALUE];
    
    for(int i = 0; i < NB_VALUE; ++i)
        tab[i] = rand();
    
    cout << "Initialisation" << endl;
    unsigned int iteration = 0;
   
    while(iteration < 30) {
        iteration++;
        // On change tous les chiffres pair par 2
        for(int i = 0; i < NB_VALUE; ++i) {
            // Si tab[i] est pair
            if(!(tab[i]&1)) {
                // Si c'est une puissance de 2         
                unsigned tmp = tab[i]&(~(tab[i]-1));
                if(tmp != tab[i]) continue;
                tmp >>= 1;
                while(tmp) {
                    tab[i] = tab[i]>>1;
                    tmp >>= 1;
                }
            }
            else
                tab[i] = tab[i] + iteration; // On rend pair le chiffre impair
        }
    }
    
    delete(tab);
    
    return 0;
}
