#ifndef __HUFFMAN_HPP__
#define __HUFFMAN_HPP__

#include <iostream>
#include <map>

#include "HuffmanTree.hpp"
#include "UtilBinary.hpp"

#define SEPARATOR_CAR '#'
#define SEPARATOR_TRAD '@'

using namespace std;

class Huffman {
  public:
    Huffman(const string text);

    void display_freq_table() const;

    code_t encode();

    map<char, code_t> getTradTable() const;

    static char code_lookup(code_t::iterator &biter,
                            const code_t::iterator &biter_end,
                            map<char, code_t> trad_table);

    static string decode(code_t code, map<char, code_t> trad_table);

    // Return binary string
    void compress(const std::string outputFileName);

    static std::string uncompress(const std::string inputFilename,
                                  const std::string outputFileName);

  private:
    void create_freq_table();

    void create_tree();

    void create_trad_table();

    code_t encode_trad_table();

    const string m_text;
    HuffmanTree *m_tree;
    vector<pair<char, unsigned>> m_freq_table;
    map<char, code_t> m_trad_table;
};

#endif /* __HUFFMAN_HPP__ */