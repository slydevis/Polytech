#ifndef __FILE_HPP_
#define __FILE_HPP__

#include <bitset>
#include <fstream>
#include <iostream>

class File {
  public:
    File(std::string filename);
    virtual ~File();

    void close();
    unsigned getSize() const;
    bool eof() const;
    std::bitset<8> getBitSet() const;
    char get() const;
    void write(char c);

  private:
    unsigned m_size;
    std::fstream *m_file;
    std::string m_filename;
};

#endif /* __FILE_HPP_ */