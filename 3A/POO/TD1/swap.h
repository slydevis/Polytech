#ifndef __SWAP_H__
#define __SWAP_H__

void swap(int &a, int &b);
void swapSansRef(int a, int b);
// inline void swapConst(const int a, const int b);

// On doit défifinir directement
inline void swapInline(int &a, int &b) { 
    int tmp = a;
    a = b;
    b = tmp;
}

#endif /* __SWAP_H__ */