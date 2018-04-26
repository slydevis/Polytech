#ifndef __HUFFMANTREE_HPP__
#define __HUFFMANTREE_HPP__

#include <iostream>

class HuffmanTree {
  public:
    // Compare two tree nodes
    struct Compare {
      public:
        bool operator()(HuffmanTree *a, HuffmanTree *b);
    };

    HuffmanTree(char c, int freq, HuffmanTree *left = NULL,
                HuffmanTree *right = NULL);

    ~HuffmanTree();

    char getCar() const;
    int getFreq() const;

    HuffmanTree *getLeft() const;
    HuffmanTree *getRight() const;

  private:
    char m_car;
    int m_freq;
    HuffmanTree *m_left;
    HuffmanTree *m_right;
};

#endif /* __HUFFMANTREE_HPP__ */