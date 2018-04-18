UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	FLAGS = -lGL -lGLU -lglut
endif

ifeq ($(UNAME_S),Darwin)
	FLAGS = -framework OpenGL -framework glut
endif

FLAGS += -std=c++11

EXE = glutFenetre.out

OBJ = GLUTFenetre.o

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(FLAGS)  

exo3: exo3.out
exo3.out: GLUTFenetres.cpp
	$(CXX) -o $@ GLUTFenetres.cpp $(FLAGS)

exo4: exo4.out
exo4.out: GLUTFenetresCouleurs.cpp
	$(CXX) -o $@ GLUTFenetresCouleurs.cpp $(FLAGS)

primitive: primitive.out
primitive.out: GLUTPrimitives.cpp
	$(CXX) -o $@ GLUTPrimitives.cpp $(FLAGS)

GLUTFenetre.o: GLUTFenetre.cpp
	$(CXX) -c GLUTFenetre.cpp $(FLAGS)

clean:
	- rm *.o exo*.out primitive.out $(EXE)