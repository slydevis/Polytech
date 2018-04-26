// #include <bitset>
// #include <iostream>
// #include <vector>

// #include "File.hpp"

// using namespace std;

/************************************************************************************

 Lecture de fichiers textes
. Réalisation d’une étude statistique sur les octets
. Modification des bits*2
. Réécriture bit à bit des valeurs modifiées dans un ou plusieurs fichiers
. Vérifier les propriétés et la taille des nouveaux fichiers

*2 On pourra écrire par exemple un bit sur deux dans un nouveau fichier, ou
couper les octets en deux parties (poids fort et poids faible), et former deux
fichiers pour des bits alternés ou des groupes de 4 bits.

6.
Ecriture du codage/décodage de Huffman, adapté au traitement d’octets. Tests sur
fichiers textes.

*************************************************************************************/
/************************************************************************************
 *                                     PART 1
 ************************************************************************************/

// int main(int argc, char **argv) {
//     if (argc != 2) {
//         std::cout << "Nombre d'argument incorrect" << std::endl;
//         return -1;
//     }

//     File file(argv[1]);
//     File file_un_bit_sur_deux("un_bit_sur_deux.txt");
//     File file_poid_fort("poid_fort.txt");
//     File file_poid_faible("poid_faible.txt");

//     std::vector<std::bitset<8>> binary_file;
//     std::vector<std::bitset<8>> binary_file_un_bit_sur_deux;
//     std::vector<std::bitset<8>> binary_file_poid_fort;
//     std::vector<std::bitset<8>> binary_file_poid_faible;

//     while (!file.eof()) {
//         std::bitset<8> bitset(file.get());
//         binary_file.push_back(bitset);
//         // std::bitset<8> c = file.getBitSet();
//         // std::cout << "BYTE = " << c.to_string() << std::endl;

//         // // Un bit sur deux dans un fichier
//         // string byte = c.to_string();
//         // for (unsigned i = 0; i < c.to_string().size(); ++i) {
//         //     if (i % 2 == 0) {
//         //         file_un_bit_sur_deux.write(byte[i]);
//         //     }
//         // }
//     }

//     // Un bit sur deux dans un fichier
//     for (unsigned i = 0; i < binary_file.size(); i = i + 2) {
//         std::bitset<8> octect;

//         std::bitset<8> tmp_poid_fort = binary_file[i];
//         std::bitset<8> tmp_poid_faible = binary_file[i + 1];

//         // std::cout << "DEBUT OCTECT = " << tmp_poid_fort.to_string()
//         //           << std::endl;

//         // Poid fort
//         unsigned cpt = 7;
//         for (int j = 7; j >= 0; j = j - 2) {
//             octect[cpt] = tmp_poid_fort[j];
//             cpt--;
//         }

//         // Poid fort
//         for (int j = 7; j >= 0; j = j - 2) {
//             octect[cpt] = tmp_poid_faible[j];
//             cpt--;
//         }

//         // std::cout << "FIN OCTECT = " << octect.to_string() << std::endl;
//         binary_file_un_bit_sur_deux.push_back(octect);
//         unsigned long n = octect.to_ulong();
//         file_un_bit_sur_deux.write((char)(n));
//     }

//     // Bit de poid fort dans un fichier
//     for (unsigned i = 0; i < binary_file.size(); i = i + 2) {
//         std::bitset<8> part1 = binary_file[i];
//         std::bitset<8> part2 = binary_file[i + 1];

//         // std::cout << "DEBUT" << std::endl;
//         // std::cout << "PART 1 = " << part1.to_string() << std::endl;
//         // std::cout << "PART 2 = " << part2.to_string() << std::endl;

//         for (unsigned j = 7; j >= 4; --j) {
//             // std::cout << "BIT = " << part2[j] << std::endl;
//             part1.set(j - 4, part2[j]);
//         }

//         // std::cout << "PART 1 = " << part1.to_string() << std::endl;

//         // std::cout << "FIN" << std::endl;

//         binary_file_poid_fort.push_back(part1);
//         unsigned long n = part1.to_ulong();
//         file_poid_fort.write((char)(n));
//     }

//     // Bit de poid faible dans un fichier
//     for (unsigned i = 0; i < binary_file.size(); i = i + 2) {
//         std::bitset<8> part1 = binary_file[i];
//         std::bitset<8> part2 = binary_file[i + 1];

//         // std::cout << "DEBUT" << std::endl;
//         // std::cout << "PART 1 = " << part1.to_string() << std::endl;
//         // std::cout << "PART 2 = " << part2.to_string() << std::endl;

//         for (int j = 3; j >= 0; --j) {
//             // std::cout << "BIT = " << part1[j] << std::endl;
//             part2.set(j + 4, part1[j]);
//         }

//         // std::cout << "PART 2 = " << part2.to_string() << std::endl;

//         // std::cout << "FIN" << std::endl;

//         binary_file_poid_faible.push_back(part2);
//         unsigned long n = part1.to_ulong();
//         file_poid_faible.write((char)(n));
//     }

//     file_un_bit_sur_deux.close();
//     file_poid_fort.close();
//     file_poid_faible.close();
//     file.close();

//     return 0;
// }

/************************************************************************************
 *                                     PART 2
 ************************************************************************************/

#include <iostream>

#include "File.hpp"
#include "Huffman.hpp"

using namespace std;

std::string text;

int main(int argc, char **argv) {
    // TODO: Add empty file protection
    // std::string text = "totoro";

    // TODO: Fix segmentation fault when less than 2 letters
    // TODO: Fix file creation if not exist
    std::string text = "";

    File file(argv[1]);

    while (!file.eof()) {
        char c = file.get();
        if (c != 0) {
            text += c;
        }
    }
    file.close();

    std::cout << "TEXT DEFAULT = " << text << std::endl;

    Huffman huff(text);
    // code_t code = huff.encode();

    // std::cout << text << " => ";
    // UtilBinary::display(code);

    // std::cout << "Decode => " << Huffman::decode(code,
    // huff.getTradTable())
    //   << std::endl;

    // std::cout << "Magical string => " <<
    // UtilBinary::bitvec_to_string(code)
    //   << std::endl;

    // code_t magicalBitVec =
    // UtilBinary::string_to_bitvec(UtilBinary::bitvec_to_string(code));

    // std::cout << "Decode Magical string => ";
    // UtilBinary::display(code);

    // std::cout << std::endl
    //           << "========= FREQUENCE TABLE  =========" << std::endl
    //           << std::endl;
    // huff.display_freq_table();

    huff.compress("fileCompressed.txt");

    Huffman::uncompress("fileCompressed.txt", "output.txt");
}
