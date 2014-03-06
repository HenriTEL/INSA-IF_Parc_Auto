EXE = parking
CC = g++
EDL = g++
INC_PATH = -I./modele -I./outils
LIB_PATH = -L./libs
LIBS = -ltp -lncurses -ltcl
EDL_FLAG = $(LIB_PATH) -o $(EXE)
CC_FLAG = $(INC_PATH) -Wall -fexceptions -c -o
MAIN = Parking
INT = Sortie.h
REA = $(INT:.h=.cpp)
OBJ = $(INT:.h=.o)
RM = rm

.PHONY : clean

all : $(EXE)

$(EXE) : $(OBJ) $(MAIN).o
	$(EDL) $(EDL_FLAG) $(OBJ) $(MAIN).o $(LIBS)

%.o : %.cpp
	@echo $@ par compilation de $<
	$(CC) $(CC_FLAG) $@ $<

clean :
	$(RM) -f $(OBJ) $(MAIN).o core
