EXE = parking
CC = g++
EDL = g++
EDL_FLAG = -I/libs -o $(EXE)
CC_FLAG = -Wall -fexceptions -c -o
CC_LIB_PATH = -L./libs
CC_LIB = -ltp
MAIN = Parking
INT = Simulation.h
REA = $(INT:.h=.cpp)
OBJ = $(INT:.h=.o)
RM = rm

.PHONY : clean

all : $(EXE)

$(EXE) : $(OBJ) $(MAIN).o
	$(EDL) $(EDL_FLAG) $(OBJ) $(MAIN).o $(LIBS)

$(MAIN).o : $(MAIN).cpp $(REA)
	$(CC) $(CC_FLAG) $@ $<

%.o : %.cpp
	echo $@ par compilation de $<
	$(CC) $(CC_FLAG) $@ $<

clean :
	@$(RM) -f $(OBJ) $(MAIN).o core
