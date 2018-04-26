#include "UtilBinary.hpp"

code_t UtilBinary::char_to_bitvec(char c) {
    code_t result;

    for (unsigned i = 0; i < 8; ++i) {
        result.push_back((c >> i) & 1);
    }

    return result;
}

code_t UtilBinary::string_to_bitvec(std::string packed) {
    code_t result;

    for (string::iterator it = packed.begin(); it != packed.end(); ++it) {
        for (unsigned i = 0; i < 8; i++) {
            result.push_back((*it >> i) & 1);
        }
    }

    return result;
}

string UtilBinary::bitvec_to_string(code_t &bitvec) {
    string result;
    size_t nbits;

    nbits = bitvec.size() & 7;

    // Write the number of "hanging bits" at the first byte
    result += static_cast<char>(nbits); // at most 7

    char byte = 0;
    for (unsigned i = 0; i < bitvec.size(); i++) {
        unsigned boff = i & 7;
        byte |= bitvec[i] << boff;
        if (boff == 7) {
            // Write a byte
            result += byte;
            byte = 0;
        }
    }
    if (nbits) {
        result += byte;
    }

    return result;
}

void UtilBinary::display(const code_t &code) {
    for (bool b : code) {
        if (b) {
            std::cout << '1';
        } else {
            std::cout << '0';
        }
    }

    std::cout << std::endl;
}
