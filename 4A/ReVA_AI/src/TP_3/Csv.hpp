#ifndef __CSV_HPP__
#define __CSV_HPP__

#include <iostream>

#include <fstream>

class CSV {
  public:
    CSV(const std::string &filename);
    void write(const std::string &str);
    void close();
    void createHeader();

  private:
    std::fstream file;
};

#endif