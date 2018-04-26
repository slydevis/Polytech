#ifndef __UTILBINARY_HPP__
#define __UTILBINARY_HPP__

#include <iostream>
#include <vector>

using namespace std;

typedef vector<bool> code_t;

class UtilBinary {
  public:
    static code_t char_to_bitvec(char c);

    static code_t string_to_bitvec(std::string packed);

    static string bitvec_to_string(code_t &bitvec);

    static void display(const code_t &code);
};

#endif /* __UTILBINARY_HPP__ */