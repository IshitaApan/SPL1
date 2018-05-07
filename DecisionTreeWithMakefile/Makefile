CXX=g++
STRIP=/usr/bin/strip
CFLAGS=-Wall
LDFLAGS=

#all: DecisionTreeBinary2 readFile
all: DecisionTreeBinary
DecisionTreeBinary.o: DecisionTreeBinary.cpp
	   $(CXX) -c $(CFLAGS) DecisionTreeBinary.cpp

#readFile.o: readFile.cpp
#	   $(CC) -c $(CFLAGS) readFile.cpp


DecisionTreeBinary: DecisionTreeBinary.o
	$(CXX) -o DecisionTreeBinary DecisionTreeBinary.o $(LDFLAGS)
	$(STRIP) DecisionTreeBinary

#readFile: readFile.o
#	$(CC) -o readFile readFile.o $(LDFLAGS)
#	$(STRIP) readFile


.PHONY: clean

clean:
	rm -rf DecisionTreeBinary *.o
#	rm -rf decisionTreeBinary2 readFile *.o



