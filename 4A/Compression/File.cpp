#include <bitset>
#include <fstream>
#include <iostream>

#include "File.hpp"

File::File(std::string filename) : m_filename(filename) {
    m_file =
        new std::fstream(filename, std::fstream::binary | std::fstream::in |
                                       std::fstream::out | std::fstream::ate);

    if (!m_file) {
        std::cerr << "Error for opening file" << std::endl;
    }

    m_size = m_file->tellg();

    // Return to the beggining
    m_file->seekg(0);

    // std::cout << "FILE SIZE = " << m_size << std::endl;
}

File::~File() { close(); }

unsigned File::getSize() const { return this->m_size; }

void File::close() { m_file->close(); }

bool File::eof() const { return m_file->eof(); }

std::bitset<8> File::getBitSet() const {
    char c = 0;

    if (!m_file->eof()) {
        m_file->get(c);
        return std::bitset<8>(c);
    }

    return std::bitset<8>();
}

char File::get() const {
    char c = 0;

    if (!m_file->eof()) {
        m_file->get(c);
    }

    return c;
}
void File::write(char c) { *m_file << c; }
