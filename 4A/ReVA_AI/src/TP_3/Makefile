UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	OPENCV_LIBS = -L/usr/local/lib -pthread -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_highgui
	INC = -I/usr/local/include/opencv2/
	OSX_LIBS=
endif

ifeq ($(UNAME_S),Darwin)
	OPENCV_LIBS = -L../../lib/ -lIlmImf -llibtiff -lopencv_imgcodecs -lippicv -llibwebp -lopencv_imgproc -llibjasper -lopencv_core -lzlib -llibjpeg -lopencv_hal -llibpng -lopencv_highgui
	OSX_LIBS = -framework OpenCL -framework Cocoa
	INC = -I../../include/
endif

FLAGS = -std=c++11

all : image_contours

debug: FLAGS += -DDEBUG -g
debug: all

# release: clean
release: FLAGS += -DRELEASE -O3
release: all

tp3.o: tp3.cpp
	$(CXX) -c tp3.cpp $(INC) $(FLAGS)

Csv.o: Csv.cpp Csv.hpp
	$(CXX) -c Csv.cpp $(INC) $(FLAGS)

Measure.o: Measure.cpp Measure.hpp
	$(CXX) -c Measure.cpp $(INC) $(FLAGS)

image_contours: Measure.o Csv.o tp3.o 
	$(CXX) -o image_contours tp3.o Measure.o Csv.o $(OSX_LIBS) $(OPENCV_LIBS) $(FLAGS)

clean :
	- rm *.o image_contours
