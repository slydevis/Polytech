EXEC = compression.out

OBJ = UtilBinary.o HuffmanTree.o Huffman.o File.o

FLAGS = -Wall -std=c++11

all: $(EXEC)

Huffman.o: Huffman.cpp Huffman.hpp
	$(CXX) -c Huffman.cpp $(FLAGS)
	
File.o: File.cpp File.hpp
	$(CXX) -c File.cpp $(FLAGS)

UtilBinary.o: UtilBinary.cpp UtilBinary.hpp
	$(CXX) -c UtilBinary.cpp $(FLAGS)

HuffmanTree.o: HuffmanTree.cpp HuffmanTree.hpp
	$(CXX) -c HuffmanTree.cpp $(FLAGS)

compression.out: main.cpp $(OBJ)
	$(CXX) -g -o $(EXEC) main.cpp $(OBJ) $(FLAGS)

release: FLAGS += -O3
release: all

clean: 
	rm $(EXEC) *.o