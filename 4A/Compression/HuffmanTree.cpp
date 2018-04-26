#include "HuffmanTree.hpp"

bool HuffmanTree::Compare::operator()(HuffmanTree *a, HuffmanTree *b) {
    return a->getFreq() > b->getFreq();
}

HuffmanTree::HuffmanTree(char c, int freq, HuffmanTree *left,
                         HuffmanTree *right)
    : m_car(c), m_freq(freq), m_left(left), m_right(right) {}

HuffmanTree::~HuffmanTree() {
    delete m_left;
    delete m_right;
}

char HuffmanTree::getCar() const { return m_car; }
int HuffmanTree::getFreq() const { return m_freq; }

HuffmanTree *HuffmanTree::getLeft() const { return m_left; }
HuffmanTree *HuffmanTree::getRight() const { return m_right; }
