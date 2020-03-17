
CXX=g++
CFLAGS =-I.
ROOTCFLAGS := $(shell  $(ROOTSYS)/bin/root-config --cflags --libs)
OBJ = K600DigitalMerge.cpp


K600DigitalMerge :  $(OBJ)
	$(CXX) -o $@ $^ $(ROOTCFLAGS) $(CFLAGS)

clean:
	rm -f *.o $(objects) K600DigitalMerge
