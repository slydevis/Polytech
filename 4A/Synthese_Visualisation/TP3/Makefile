UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	FLAGS = -lGL -lGLU -lglut
endif

ifeq ($(UNAME_S),Darwin)
	FLAGS = -framework OpenGL -framework glut
endif

FLAGS += -std=c++11

EXE = tp3.out

OBJ = tp3.o

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(FLAGS)  

tp3.o: tp3.cpp
	$(CXX) -c tp3.cpp $(FLAGS)

clean:
	- rm *.o $(EXE)