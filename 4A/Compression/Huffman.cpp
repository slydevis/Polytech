#include "Huffman.hpp"

#include <queue>

#include "File.hpp"

using namespace std;

Huffman::Huffman(const string text) : m_text(text) {
    create_freq_table();
    create_tree();
    create_trad_table();
}

void Huffman::display_freq_table() const {
    for (std::pair<char, unsigned> e : m_freq_table) {
        std::cout << '[' << e.first << ", " << e.second << ']' << std::endl;
    }
}

code_t Huffman::encode() {
    code_t result;

    for (char c : m_text) {
        code_t code = m_trad_table[c];
        result.insert(result.end(), code.begin(), code.end());
    }

    return result;
}

map<char, code_t> Huffman::getTradTable() const { return m_trad_table; }

char Huffman::code_lookup(code_t::iterator &biter,
                          const code_t::iterator &biter_end,
                          map<char, code_t> trad_table) {
    code_t code;

    while (true) {
        if (biter == biter_end) {
            throw std::out_of_range("No more bits");
        }

        // std::cout << "BIT = " << *biter << std::endl;

        code.push_back(*biter);
        ++biter;

        // std::cout << "CODE = ";
        // UtilBinary::display(code);

        for (map<char, code_t>::iterator it = trad_table.begin();
             it != trad_table.end(); ++it) {
            if (code == it->second) {
                return it->first;
            }
        }
    }
}

string Huffman::decode(code_t code, map<char, code_t> trad_table) {
    string result;

    code_t::iterator biter = code.begin();

    while (true) {
        try {
            result += Huffman::code_lookup(biter, code.end(), trad_table);
        } catch (const std::out_of_range &oor) {
            // Iterator exhausted.
            break;
        }
    }

    return result;
}

// Return binary string
void Huffman::compress(const std::string outputFileName) {
    code_t code_header = encode_trad_table();
    code_t separator = UtilBinary::char_to_bitvec(SEPARATOR_TRAD); // NULL (0)
    code_t code_content = encode();

    code_t code;
    code.insert(code.end(), code_header.begin(), code_header.end());
    code.insert(code.end(), separator.begin(), separator.end());
    code.insert(code.end(), code_content.begin(), code_content.end());

    int nbAdded = 0;
    int alternate = false;
    while (code.size() % 8 != 0) {
        // TODO: Add char with value of padding
        // Default = 0
        code.push_back(alternate);
        alternate = !alternate;
        nbAdded++;
    }

    std::cout << "NB ADDED = " << nbAdded << std::endl;
    string outputStr = UtilBinary::bitvec_to_string(code);
    outputStr.push_back(nbAdded);
    // outputStr.push_back(0);

    // std::cout << UtilBinary::bitvec_to_string(code) << std::endl;
    // std::cout << decode(code_content, m_trad_table) << std::endl;

    std::cout << "==== CODE COMPRESSED (" << code.size()
              << ") ====" << std::endl;
    // UtilBinary::display(code);

    std::cout << "==== RESULT ===== " << std::endl << outputStr << std::endl;

    // UtilBinary::display(UtilBinary::string_to_bitvec(outputStr));

    File output(outputFileName);
    output.write(outputStr);
    output.close();
}

std::string Huffman::uncompress(const std::string inputFilename,
                                const std::string outputFileName = "") {

    File input(inputFilename);
    string str = "";

    while (!input.eof()) {
        str += input.get();
    }

    input.close();

    // Header reading
    map<char, code_t> trad_table;
    unsigned i = 0;

    while (true) {
        std::cout << "==== STEP " << i << " ====" << std::endl;
        char c = str[0];

        if (c == SEPARATOR_TRAD) {
            break;
        }

        str.erase(0, 1);
        ++i;

        if (c == 1) { // Start of heading
            continue;
        }

        char token = c;
        code_t code;

        while (c != SEPARATOR_CAR && c != SEPARATOR_TRAD && c != '\0') {
            c = str[0];
            str.erase(0, 1);

            if (c == SEPARATOR_CAR || c == SEPARATOR_TRAD || c == '\0')
                break;

            if (c == '0') {
                code.push_back(false);
            } else {
                code.push_back(true);
            }
        }

        if (token != '\0') {
            trad_table.insert(make_pair(token, code));
        }

        if (c == SEPARATOR_TRAD) {
            break;
        }
    }

    // Content reading
    // Remove NTCTS character because it's a string
    for (unsigned i = 0; i < 1; ++i) {
        str.pop_back();
    }

    // Get nbPadding
    unsigned nbPadding = (int)str[str.size() - 1];
    str.pop_back();

    code_t code_content = UtilBinary::string_to_bitvec(str);

    // TODO: Remove nbPadding
    for (unsigned i = 0; i < nbPadding; ++i) {
        code_content.pop_back();
    }

    string uncompressedStr = Huffman::decode(code_content, trad_table);

    std::cout << "==== UNCOMPRESSED ====" << std::endl;
    std::cout << uncompressedStr << std::endl;

    // TODO: Store result in file
    if (outputFileName != "") {
        File output(outputFileName);
        output.write(uncompressedStr);
        output.close();
    }

    return uncompressedStr;
}

void Huffman::create_freq_table() {
    map<char, unsigned> freq;

    for (unsigned i = 0; i < m_text.size(); ++i) {
        // If not found
        if (freq.find(m_text[i]) == freq.end()) {
            freq.insert(make_pair(m_text[i], 1));
        }

        freq[m_text[i]] += 1;
    }

    for (map<char, unsigned>::iterator it = freq.begin(); it != freq.end();
         ++it) {
        m_freq_table.push_back(make_pair(it->first, it->second));
    }
}

void Huffman::create_tree() {
    // First build a vector with lowest first
    priority_queue<HuffmanTree *, vector<HuffmanTree *>, HuffmanTree::Compare>
        lowest_heap;

    // Create all leaf
    for (vector<pair<char, unsigned>>::iterator it = m_freq_table.begin();
         it != m_freq_table.end(); ++it) {
        HuffmanTree *leaf = new HuffmanTree(it->first, it->second);
        lowest_heap.push(leaf);
    }

    HuffmanTree *root = NULL;

    // Merge two lowest frequence leaf nodes
    while (lowest_heap.size() > 1) {
        HuffmanTree *right;
        HuffmanTree *left;

        left = lowest_heap.top();
        lowest_heap.pop();

        right = lowest_heap.top();
        lowest_heap.pop();

        root =
            new HuffmanTree(0, left->getFreq() + right->getFreq(), left, right);
        lowest_heap.push(root);
    }

    m_tree = root;
}

void Huffman::create_trad_table() {
    deque<pair<HuffmanTree *, code_t>> q;

    q.push_back(make_pair(m_tree, code_t()));

    while (!q.empty()) {
        HuffmanTree *node = q.front().first;
        code_t code = q.front().second;
        q.pop_front();

        HuffmanTree *left = node->getLeft();
        HuffmanTree *right = node->getRight();

        if (left) {
            code_t code_cp(code);
            // Left => 0
            // Right => 1
            code.push_back(0);
            code_cp.push_back(1);

            q.push_back(make_pair(left, code));
            q.push_back(make_pair(right, code_cp));
        } else {
            // Leaf node contains the character
            m_trad_table.insert(make_pair(node->getCar(), code));

            cout << "(" << node->getCar() << ", ";

            for (unsigned i = 0; i < code.size(); i++) {
                cout << code[i];
            }

            cout << ")" << endl;
        }
    }
}

code_t Huffman::encode_trad_table() {
    code_t code_table;

    code_t separator =
        UtilBinary::char_to_bitvec(SEPARATOR_CAR); // Group Separotor (29)

    for (map<char, code_t>::iterator it = m_trad_table.begin();
         it != m_trad_table.end(); ++it) {

        code_t code_car = UtilBinary::char_to_bitvec(it->first);
        code_table.insert(code_table.end(), code_car.begin(), code_car.end());

        for (bool b : it->second) {
            code_t code_bit;

            if (b) {
                code_bit = UtilBinary::char_to_bitvec('1');
            } else {
                code_bit = UtilBinary::char_to_bitvec('0');
            }

            code_table.insert(code_table.end(), code_bit.begin(),
                              code_bit.end());
        }

        code_table.insert(code_table.end(), separator.begin(), separator.end());
    }

    // Remove last separator
    for (unsigned i = 0; i < 8; ++i) {
        code_table.pop_back();
    }

    return code_table;
}
