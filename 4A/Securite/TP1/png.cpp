#include <iostream>
#include <fstream>
#include <cstring> // memset
#include <vector>

using namespace std;

void error(string message, int line, string function) {
	cerr << endl << message << " (Line : " << line << ", Function : " << function << ")" << endl;
	exit(-1);
}

enum ChunkType {
	IHDR = 1,
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

int toLittleEndian(int d) {
	int a;
	unsigned char *dst = (unsigned char *) &a;
	unsigned char *src = (unsigned char *) &d;

	dst[0] = src[3];
	dst[1] = src[2];
	dst[2] = src[1];
	dst[3] = src[0];

	return a;
}


class Chunk {
private:
int cursorSecret = 0;
public:
int lenght;
ChunkType type;
vector<char> data;
int crc

Chunk() {
	lenght = 0;
	type = IHDR;
	crc = 0;
}

Chunk(const Chunk &chunk) {
	lenght = chunk.lenght;
	type = chunk.type;
	data = chunk.data;
	crc = chunk.crc;
}

void setType(string typeChunk) {
	cout << "Chunk type = " << typeChunk << "" << endl;
	if (strcmp(typeChunk.c_str(), "IHDR") == 0)
		type = IHDR;
	else if (strcmp(typeChunk.c_str(), "PLTE") == 0)
		type = PLTE;
	else if (strcmp(typeChunk.c_str(), "IDAT") == 0)
		type = IDAT;
	else if (strcmp(typeChunk.c_str(), "IEND") == 0)
		type = IEND;
	else if (strcmp(typeChunk.c_str(), "bKGD") == 0)
		type = bKGD;
	else if (strcmp(typeChunk.c_str(), "cHRM") == 0)
		type = cHRM;
	else if (strcmp(typeChunk.c_str(), "gAMA") == 0)
		type = gAMA;
	else if (strcmp(typeChunk.c_str(), "hIST") == 0)
		type = hIST;
	else if (strcmp(typeChunk.c_str(), "pHYs") == 0)
		type = pHYs;
	else if (strcmp(typeChunk.c_str(), "sBIT") == 0)
		type = sBIT;
	else if (strcmp(typeChunk.c_str(), "tEXT") == 0)
		type = tEXT;
	else if (strcmp(typeChunk.c_str(), "tIME") == 0)
		type = tIME;
	else if (strcmp(typeChunk.c_str(), "tRNS") == 0)
		type = tRNS;
	else if (strcmp(typeChunk.c_str(), "zTXt") == 0)
		type = zTXt;
	else
		error("Unknown chunk " + typeChunk, __LINE__, __FUNCTION__);
}

string getType() const {
	switch (type) {
	case IHDR:
		return "IHDR";
	case PLTE:
		return "PLTE";
	case IDAT:
		return "IDAT";
	case IEND:
		return "IEND";
	case bKGD:
		return "bKGD";
	case cHRM:
		return "cHRM";
	case gAMA:
		return "gAMA";
	case hIST:
		return "hIST";
	case pHYs:
		return "pHYs";
	case sBIT:
		return "sBIT";
	case tEXT:
		return "tEXT";
	case tIME:
		return "tIME";
	case tRNS:
		return "tRNS";
	case zTXt:
		return "zTXt";
	default:
		return "";
	}
}

friend ostream &operator<<(ostream &os, const Chunk &chunk) {
	// Write lenght
//        int tmp = toLittleEndian(chunk.lenght);
//        os.write((char *) &tmp, sizeof(int));

	// Write type
//        cout << "SAVE " << chunk.getType() << endl;
//        os << chunk.getType();

	// Write Data
	for (unsigned i = 0; i < chunk.data.size(); ++i)
		os << chunk.data[i];

	// Write CRC
//        tmp = toLittleEndian(chunk.crc);
//        os.write((char *) &tmp, sizeof(int));
}

void write_lsb(unsigned char secret) {

}
};

class PNG {
unsigned char signature[8];     // 8 octets
Chunk ihdr;
vector<Chunk> otherChunk;
Chunk idat;
Chunk iend;

bool validFileSignature() {
	const int validSignature[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

	for (short i = 0; i < 8; ++i)
		if (signature[i] != validSignature[i])
			return false;

	return true;
}

Chunk readChunk(ifstream &file) {
	Chunk chunk;

	int lenght;
	file.read((char *) &lenght, sizeof(int));
	lenght = toLittleEndian(lenght);

	chunk.lenght = lenght;

	// Read type
	string type;
	for (int i = 0; i < 4; ++i) {
		char c;
		file.read(&c, 1);
		type.push_back(c);
	}

	chunk.setType(type);

	for (unsigned i = 0; i < chunk.lenght; ++i) {
		char c;
		file.read(&c, sizeof(char));

		chunk.data.push_back(c);
	}

	int crc;
	file.read((char *) &crc, sizeof(int));
	crc = toLittleEndian(crc);

	chunk.crc = crc;

	return chunk;
}

public:
PNG() {
};

PNG(string filename) {
	this->open(filename);
}

void open(const string &filename) {
	cout << "OPEN " << filename << endl;

	ifstream file(filename, ios::binary);

	if (!file.is_open())
		error("Error opening picture file", __LINE__, __FUNCTION__);

	// Read file signature
	for (unsigned char &c : signature)
		file.read((char *) &c, 1);

	if (!validFileSignature())
		error("Error file signature incorrect", __LINE__, __FUNCTION__);

	while (!file.eof()) {
		Chunk chunk = readChunk(file);
		cout << "type = " << chunk.type << endl;
		if (chunk.type == IHDR)
			ihdr = chunk;
		else if (chunk.type == IDAT) {
			cout << "ICI " << endl;
			idat = chunk;
			cout << "IDAT TYPE = " << idat.getType() << endl;
		} else if (chunk.type == IEND) {
			iend = chunk;
			break;
		} else
			otherChunk.push_back(chunk);
	}

	file.close();
}

void save(const string &filename) {
	ofstream output(filename, ios::binary | ios::out);

	if (!output.is_open())
		error("Error opening output picture", __LINE__, __FUNCTION__);

	// Write PNG signature
//        for (unsigned char c: signature)
//            output << c;

	// Write ihdr chunck
//        output << ihdr;

//        for (const Chunk &chunk: otherChunk)
//            output << chunk;

	output << idat;

//        output << iend;

	output.close();
}

void hide_by_lsb(unsigned char secret) {
	idat.write_lsb(secret);
}
};

int main() {
	PNG png("picture.png");
	png.save("output_picture.png");
}
