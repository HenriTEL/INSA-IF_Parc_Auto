EXE = parking
CC = g++
EDL = g++
EDL_FLAG = -o $(EXE)
CC_FLAG = -Wall -fexceptions -c -std=gnu++11
CC_LIB_PATH = -L./libs
CC_LIB = -ltp
MAIN = Parking
INT = Simulation.h
REA = $(INT:.h=.cpp)
OBJ = $(INT:.h=.o)
ClEAN = efface


PHONY : $(CLEAN)

all : $(EXE)

$(EXE) : $(OBJ) $(MAIN).o
	$(EDL) $(EDL_FLAG) $(OBJ) $(MAIN).o $(LIBS)

$(MAIN).o : $(MAIN) $(REA)
	$(CC) -o $@ $(CC_FLAG) $(MAIN)

%.o : %.cpp
	echo compilation de $<
	$(CC) $@ $(CC_FLAG) $<

$(CLEAN) :
	rm -f $(OBJ) $(MAIN).o core
