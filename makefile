C = g++ -O2 -I./sdl/include -L.
CCFLAG = -Wall -fexceptions -c -std=gnu++11
LIBS = -lm -lSDL -lpthread -ldl
MAIN = main.cpp
CLASSH = Graph.h ServerStats.h Log.h MapExt.h StringExt.h
CLASS = $(INT:.h=.cpp)
OBJ = $(CLASSH:.h=.o)
ClEAN = efface


PHONY : $(CLEAN)

all: main

main: $(OBJ) main.o
	$(CC) -o analog $(OBJ) main.o $(LIBS)

main.o: $(MAIN) $(CLASSH)
	$(CC) -o $@ -c $(CCFLAG) $(MAIN)

%.o : %.cpp
	echo compilation de $<
	$(CC) -o $@ -c $(CCFLAG) $<


$(CLEAN) :
	rm -f $(OBJ) main.o core
