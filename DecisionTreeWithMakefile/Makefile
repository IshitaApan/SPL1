CXX=g++
STRIP=/usr/bin/strip
CFLAGS=-Wall
LDFLAGS=

all: decisionTreeBinary2 readFile

decisionTreeBinary2.o: decisionTreeBinary2.cpp
	   $(CC) -c $(CFLAGS) decisionTreeBinary2.cpp

readFile.o: readFile.cpp
	   $(CC) -c $(CFLAGS) readFile.cpp


decisionTreeBinary2: decisionTreeBinary2.o
	$(CC) -o decisionTreeBinary2 decisionTreeBinary2.o $(LDFLAGS)
	$(STRIP) decisionTreeBinary2

readFile: readFile.o
	$(CC) -o readFile readFile.o $(LDFLAGS)
	$(STRIP) readFile


.PHONY: clean

clean:
	rm -rf decisionTreeBinary2 readFile *.o


