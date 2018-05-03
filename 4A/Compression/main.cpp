#include <iostream>

#include "File.hpp"
#include "Huffman.hpp"

using namespace std;

std::string text;

void part1(string filename) {
    File file(filename);

    text = "";
    while (!file.eof()) {
        char c = file.get();
        std::cout << "char (" << (int)c << ")= " << c << std::endl;
        text += c;
    }

    code_t binary_file = UtilBinary::string_to_bitvec(text);
    std::cout << "Original (" << text << ") : ";
    UtilBinary::display(binary_file);

    // Un bit sur deux dans un fichier
    File file_un_bit_sur_deux("un_bit_sur_deux.txt", true);
    code_t binary_file_un_bit_sur_deux;

    for (unsigned i = 0; i < binary_file.size(); i += 2) {
        binary_file_un_bit_sur_deux.push_back(binary_file[i]);
    }

    std::cout << "Un bit sur deux = ";
    UtilBinary::display(binary_file_un_bit_sur_deux);
    file.close();

    string res = UtilBinary::bitvec_to_string(binary_file_un_bit_sur_deux);
    file_un_bit_sur_deux.write(res);
    file_un_bit_sur_deux.close();

    // Bit de poid fort dans un fichier
    File file_poid_fort("poid_fort.txt", true);
    code_t binary_file_poid_fort;

    for (unsigned i = 0; i < binary_file.size(); i += 8) {
        for (unsigned j = 0; j < 4; ++j) {
            binary_file_poid_fort.push_back(binary_file[i + j]);
        }
    }

    std::cout << "Poid fort = ";
    UtilBinary::display(binary_file_poid_fort);
    res = UtilBinary::bitvec_to_string(binary_file_poid_fort);
    file_poid_fort.write(res);
    file_poid_fort.close();

    // Bit de poid faible dans un fichier
    File file_poid_faible("poid_faible.txt", true);
    code_t binary_file_poid_faible;

    for (unsigned i = 4; i < binary_file.size(); i += 8) {
        for (unsigned j = 0; j < 4; ++j) {
            binary_file_poid_faible.push_back(binary_file[i + j]);
        }
    }

    std::cout << "Poid faible = ";
    UtilBinary::display(binary_file_poid_faible);
    res = UtilBinary::bitvec_to_string(binary_file_poid_faible);
    file_poid_faible.write(res);
    file_poid_faible.close();
}

void part2(string filename) {
    // TODO: Fix segmentation fault when less than 2 letters
    // TODO: Fix file creation if not exist
    std::string text = "";

    File file(filename);

    if (file.getSize() == 0) {
        std::cerr << "Le fichier à compresser est vide" << std::endl;
        return;
    }

    while (!file.eof()) {
        char c = file.get();
        if (c != 0) {
            text += c;
        }
    }
    file.close();

    std::cout << "TEXT DEFAULT = " << text << std::endl;

    Huffman huff(text);

    huff.compress("fileCompressed.txt");

    Huffman::uncompress("fileCompressed.txt", "output.txt");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage : ./compression.out filename" << std::endl;
        return -1;
    }

    /************************************************************************************
     *                                     PART 1
     ************************************************************************************/
    part1(argv[1]);

    /************************************************************************************
     *                                     PART 2
     ************************************************************************************/
    part2(argv[1]);
}
