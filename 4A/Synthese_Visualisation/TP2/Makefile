UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	FLAGS = -lGL -lGLU -lglut
endif

ifeq ($(UNAME_S),Darwin)
	FLAGS = -framework OpenGL -framework glut
endif

FLAGS += -std=c++11

EXE = tp2.out

OBJ = tp2.o

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(FLAGS)  

tp2.o: tp2.cpp
	$(CXX) -c tp2.cpp $(FLAGS)

clean:
	- rm *.o $(EXE)