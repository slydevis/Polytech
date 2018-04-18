#include <iostream>
#include <fstream>
#include <cstring> // memset
#include <sstream>

#include <openssl/aes.h>
#include <vector>
#include <limits.h>

using namespace std;

#define KEY_LENGHT 128
const string CKEY = "c77f52e8b1ca1087055b47b47f67b078";

/***********************************************************************************************************************
 *                                             Sujet
 * 1) Ecrire un programme qui chiffre en AES-CBC en utilisant la librairie OPENSSL,
 * Tout fichier de n'importe quelle format
 * 2) Qui cache le chiffré dans une image PNG en utilisant la technique LSB
 * 3) Qui retrouve le plaintext à partir d'une image
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *                                          Useful functions
 **********************************************************************************************************************/

void error(string message, int line, string function) {
    cerr << endl << message << " (Line : " << line << ", Function : " << function << ")" << endl;
    exit(-1);
}

/***********************************************************************************************************************
 *                                AES CBC encryption/decryption functions
 **********************************************************************************************************************/

/**
 * Crypt a plain text with AES-CBC
 * @param plaintext
 * @param iv
 * @return
 */
string encrypt_aes(const string plaintext, unsigned char iv[]) {
    size_t inputslength = plaintext.length();
    unsigned char aes_input[inputslength];
    unsigned char aes_key[KEY_LENGHT];
    memset(aes_input, 0, inputslength / 8);
    memset(aes_key, 0, KEY_LENGHT / 8);
    strcpy((char *) aes_input, plaintext.c_str());
    strcpy((char *) aes_key, CKEY.c_str());

    // buffers for encryption and decryption
    const size_t encslength = ((inputslength + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char enc_out[encslength];
    unsigned char dec_out[inputslength];
    memset(enc_out, 0, sizeof(enc_out));
    memset(dec_out, 0, sizeof(dec_out));

    AES_KEY enc_key;
    AES_set_encrypt_key(aes_key, KEY_LENGHT, &enc_key);
    AES_cbc_encrypt(aes_input, enc_out, inputslength, &enc_key, iv, AES_ENCRYPT);

    stringstream ss;
    for (int i = 0; i < encslength; i++) {
        ss << enc_out[i];
    }

    return ss.str();
}

/**
 * Decrypt a AES-CBC cipher text
 * @param ciphertext
 * @param iv
 * @return
 */
string decrypt_aes(const string ciphertext, unsigned char iv[]) {
    size_t inputslength = 1000;
    unsigned char aes_key[KEY_LENGHT];
    memset(aes_key, 0, KEY_LENGHT / 8);
    strcpy((char *) aes_key, CKEY.c_str());

    unsigned char enc_out[inputslength];
    memset(enc_out, 0, inputslength / 8);
    strcpy((char *) enc_out, ciphertext.c_str());

    const size_t encslength = ((inputslength + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    unsigned char dec_out[inputslength];
    memset(dec_out, 0, sizeof(dec_out));

    AES_KEY dec_key;

    AES_set_decrypt_key(aes_key, KEY_LENGHT, &dec_key);
    AES_cbc_encrypt(enc_out, dec_out, encslength, &dec_key, iv, AES_DECRYPT);

    string ss((char *) dec_out);
    return ss;
}

/***********************************************************************************************************************
 *                            Hide/Extract a cipher into a picture by LSB method functions
 **********************************************************************************************************************/

enum ChunkType {
    IHDR,
    PLTE,
    IDAT,
    IEND,
    bKGD,
    cHRM,
    gAMA,
    hIST,
    pHYs,
    sBIT,
    tEXT,
    tIME,
    tRNS,
    zTXt,
};

//template <ChunckType T>
class Chunk {
public:
    char length[4];
    uint32_t deciLength = 0;
    ChunkType type;
    vector<unsigned char> data;
    unsigned char crc[4];

    void setType(string type) {
        cout << "Chunk type = #" << type << "#" << endl;
        if(strcmp(type.c_str(), "IHDR") == 0)
            type = IHDR;
        else if(strcmp(type.c_str(), "PLTE") == 0)
            type = PLTE;
        else if(strcmp(type.c_str(), "IDAT") == 0)
            type = IDAT;
        else if(strcmp(type.c_str(), "IEND") == 0)
            type = IEND;
        else if(strcmp(type.c_str(), "bKGD") == 0)
            type = bKGD;
        else if(strcmp(type.c_str(), "cHRM") == 0)
            type = cHRM;
        else if(strcmp(type.c_str(), "gAMA") == 0)
            type = gAMA;
        else if(strcmp(type.c_str(), "hIST") == 0)
            type = hIST;
        else if(strcmp(type.c_str(), "pHYs") == 0)
            type = pHYs;
        else if(strcmp(type.c_str(), "sBIT") == 0)
            type = sBIT;
        else if(strcmp(type.c_str(), "tEXT") == 0)
            type = tEXT;
        else if(strcmp(type.c_str(), "tIME") == 0)
            type = tIME;
        else if(strcmp(type.c_str(), "tRNS") == 0)
            type = tRNS;
        else if(strcmp(type.c_str(), "zTXt") == 0)
            type = zTXt;
        else
            error("Unknown chunk " + type, __LINE__, __FUNCTION__);
    }
    void updateDeciLength() {
//        for(unsigned i = 0; i < 4; ++i)
//            deciLength = (unsigned) length[i];

        // TOTAL = 179502
        // = 0 + 2*16^2 + 189*16^3 + 46*16^4

//        cout << "Test calcul = " << (0 + 2*pow(16, 1) + 189*pow(16, 2)+ 46*pow(16, 3)) << endl;
//        cout << "length[0] = " << (unsigned) length[0] << endl; // 0 = 00
//        cout << "length[1] = " << (unsigned) length[1] << endl; // 2 = 02
//        cout << "length[2] = " << (unsigned) length[2] << endl; // 189 = BD
//        cout << "length[3] = " << (unsigned) length[3] << endl; // 46 = 2E

//        deciLength = ((static_cast<uint32_t>(length[0]) << 24)
//                      | (static_cast<uint32_t>(length[1]) << 16)
//                      | (static_cast<uint32_t>(length[2]) << 8)
//                      | (static_cast<uint32_t>(length[3])));

        cout << "TENTATIVE = " << length << endl;
        //cout << "LENGTH = " << deciLength << endl;
        if(type == IHDR)
            deciLength = 13;
        else if(type == IDAT)
            deciLength = 179502;
        else if(type == IEND)
            deciLength = 0;
    }
};

class PNG {
    unsigned char signature[8]; // 8 octets
    Chunk ihdr;
    vector<Chunk> otherChunk;
    Chunk idat;
    Chunk iend;

    /**
     * Valid file signature for PNG file
     * @return boolean
     */
    bool validFileSignature() {
        const int validSignature[] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };

        for(short i = 0; i < 8; ++i)
            if(signature[i] != validSignature[i])
                return false;

        return true;
    }

    Chunk readChuck(ifstream &file) {
        Chunk chunk;

        // Read length
        file.read(chunk.length, 4);

//        for(unsigned i = 0; i < 4; ++i) {
//            char c;
//            file.read(&c, 1);
//            chunk.length[i] = c;
//        }

        for(unsigned i = 0; i < 4; ++i)
            cout << "chunk.length[" << i << "] = " << (unsigned) chunk.length[i] << endl;

        unsigned int l = ((chunk.length[0] << 24) & 0xFF000000U)
                         | ((chunk.length[1] << 16) & 0x00FF0000U)
                         | ((chunk.length[2] <<  8) & 0x0000FF00U)
                         | ( chunk.length[3]        & 0x000000FFU);

        cout << "length = " << l << endl;

        // Read type
        unsigned char typeTmp[4];

        for (unsigned char &c : typeTmp)
            file.read((char*)&c, 1);

        string type((char*) typeTmp);
        chunk.setType(type);

        // Read datas
        for(unsigned i = 0; i < chunk.deciLength; ++i) {
            unsigned char c;
            file.read((char*)&c, 1);
            chunk.data.push_back(c);
        }

        // Read CRC
        for(unsigned char &c : chunk.crc)
            file.read((char*)&c, 1);

        cout << "FIN LECTURE DE CHUNK" << endl;

        return chunk;
    }
public:
    PNG(const string &path) {
        this->open(path);
    }

    /**
     *
     * @param path
     */
    void open(const string &path) {
        ifstream file(path, ios::binary);

        if (!file.is_open())
            error("Error opening picture file", __LINE__, __FUNCTION__);

        // Read file signature
        for (unsigned char &c : signature) {
            file.read((char*)&c, 1);
        }

        if(!validFileSignature())
            error("Error file signature incorrect", __LINE__, __FUNCTION__);

        while(!file.eof()) {
            Chunk chunk = readChuck(file);
            if(chunk.type == IHDR)
                ihdr = chunk;
            else if(chunk.type == IDAT)
                idat = chunk;
            else if(chunk.type == IEND)
                iend = chunk;
            else
                otherChunk.push_back(chunk);
        }

        file.close();
    }

    void save(string path) {
        ofstream output(path, ios::binary | ios::out);

        if (!output.is_open())
            error("Error opening output picture", __LINE__, __FUNCTION__);

        // Write PNG signature
        for (unsigned char c: signature)
            output << c;

        // Write ihdr chunck
//        output << ihdr;
//
//        for(Chunk chunk: otherChunk)
//            output << otherChunk;
//
//        output << idat;
//
//        output << iend;

        output.close();
    }

    void write_lsb(unsigned char secret) {
//        for (int i = 0; i < sizeof(char) * 8; ++i) {
//            char data;
//            picture.read(&data, 1);
//
//            if(i == 0) {
//                printf("data = %X\n", data & 0xff);
//
//                printf("secret = %X\n", secret);

//        unsigned char secretByte = (secret & (1 << 7));
//
//        if (secretByte == 128)
//            secretByte = 0xFF;
//        else
//            secretByte = 0xFE;
//
//        printf("secretByte = %X\n", secretByte & 0xff);
//
//            secret = secret << 1;
//
//            data = data & 0xff & secretByte;

//                printf("output = %X\n", data & 0xff);
//            }
//
//            output.write(&data, sizeof(data));
//        }
    }

    char read_lsb(char data) {

    }
};

/**
 * Hide a IV into an output file by LSB method
 * @param iv
 * @param picture
 */
void hide_iv(const unsigned char iv[], const string picture_path) {
    PNG png(picture_path);

    for(unsigned i = 0; i < AES_BLOCK_SIZE; ++i)
        png.write_lsb(iv[i]);

    png.save("output_" + picture_path);
}

/**
 * Hide a ciphertext into an output file with LSB method
 * @param ciphertext
 * @param picture
 */
void hide_cipher(const string ciphertext, const string picture_path) {
//    ifstream picture(picture_path, ios::binary);
//
//    if (!picture.is_open())
//        error("Error opening picture file", __LINE__, __FUNCTION__);
//
//    ofstream output("output_" + picture_path, ios::binary | ios::app);
//
//    if (!output.is_open())
//        error("Error opening output picture", __LINE__, __FUNCTION__);
//
//    picture.seekg(PNG_HEADER_SIZE + AES_BLOCK_SIZE * 8);
//
//    for (char c : ciphertext)
//        write_lsb(picture, output, (unsigned char) c);
//
//    // Write end of picture
//    while(!picture.eof()) {
//        char c;
//        picture.read(&c, 1);
//
//        if(picture.eof())
//            break;
//
//        output.write(&c, sizeof(c));
//    }
//
//    picture.close();
//    output.close();
}

/**
 *
 * @param picture
 * @return
 */
void extract_iv(const string picture, unsigned char iv[]) {

}

/**
 *
 * @param picture
 * @return
 */
string extract_cipher(const string picture) {
    return "";
}

void encrypt() {
    string filename;
    cout << "Enter name to encrypt : " << endl;
    cin >> filename;

    ifstream input_file(filename);

    if (!input_file.is_open())
        error("Error opening input file", __LINE__, __FUNCTION__);

    string line;

    // TODO : Mettre l'IV au debut dans l'image
    srand(time(NULL));
    unsigned char iv[AES_BLOCK_SIZE];
    for(unsigned i = 0; i < AES_BLOCK_SIZE; ++i)
        iv[i] = (unsigned char)(rand()%CHAR_MAX);
//    memset(iv, 0x00, AES_BLOCK_SIZE);

    // Create a iv save variable to decrypt
    unsigned char save_iv[AES_BLOCK_SIZE];
    for (unsigned i = 0; i < AES_BLOCK_SIZE; ++i)
        save_iv[i] = iv[i];

    string text;
    while (getline(input_file, line)) {
        text += line + "\n";
    }

    // Encrypt file
    cout << "Plaintext original = " << text << endl;

    string cipherText = encrypt_aes(text, iv);

    // Reload iv from save
    for (unsigned i = 0; i < AES_BLOCK_SIZE; ++i)
        iv[i] = save_iv[i];

    cout << "Cipher = " << cipherText << endl;

    // Hide cipher in picture
    string picture = "picture.png";
    hide_iv(iv, picture);
//    hide_cipher(cipherText, picture);

    // Extract cipher from picture
//    picture = "output_picture.png";
//    extract_iv(picture, iv);
//    cipherText = extract_cipher(picture);

//    line = decrypt_aes(cipherText, iv);
//    cout << "Plaintext = " << line << endl;
//

    ofstream out("output_" + filename);

    for(int i = 0; i < AES_BLOCK_SIZE; ++i)
        out.write((char *)(&iv[i]), sizeof(iv[i]));

    out.write(cipherText.c_str(), cipherText.size());

    out.close();
    input_file.close();
}

void decrypt() {
    string filename;
    cout << "Enter name to decrypt : " << endl;
    cin >> filename;

    ifstream input_file(filename);

    unsigned char iv[AES_BLOCK_SIZE];
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        char c;
        iv[i] = 0;
        input_file.get(c);
        iv[i] = (unsigned char) c;
    }

    string ciphertext;
    while(!input_file.eof()) {
        char c;
        input_file.read(&c, 1);
        ciphertext += c;
    }

    string line = decrypt_aes(ciphertext, iv);
    cout << "plaintext = " << line;
}

int main(int argc, char *argv[]) {
    int choice;

    cout << "Que faire ?" << endl;
    cout << "1 : Encrypt file" << endl;
    cout << "2 : Decrypt file" << endl;
    cin >> choice;

    switch (choice) {
        case 1:
            encrypt();
            break;
        case 2:
            decrypt();
            break;
        default:
            error("Command not found", __LINE__, __FUNCTION__);
    }

    return 0;
}