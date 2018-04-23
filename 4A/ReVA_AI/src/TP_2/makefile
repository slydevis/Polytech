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

all : image_expansion

compute_histogram.o: compute_histogram.cpp
	$(CXX) -c compute_histogram.cpp $(INC)

image_expansion.o: image_expansion.cpp
	$(CXX) -c image_expansion.cpp $(INC)

image_expansion: image_expansion.o compute_histogram.o
	$(CXX) -o image_expansion image_expansion.o compute_histogram.o $(OSX_LIBS) $(OPENCV_LIBS)

clean :
	rm *.o image_expansion
