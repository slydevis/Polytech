UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	FLAGS = -lGL -lGLU -lglut
	FLAGS += -lsfml-system -lsfml-audio
endif

ifeq ($(UNAME_S),Darwin)
	FLAGS = -framework OpenGL -framework glut
endif

FLAGS += -std=c++11

EXE = tp4.out

OBJ = tp4.o

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(FLAGS)

tp4.o: tp4.cpp
	$(CXX) -c tp4.cpp $(FLAGS)

clean:
	- rm *.o $(EXE)
