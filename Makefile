CC=g++
CFLAGS=-fopenmp -c -Wall
LDFLAGS=-fopenmp
SOURCES=draw.cpp draw.h gamecontroller.cpp gamecontroller.h keys.cpp levelmap.cpp levelmap.h main.cpp mapBlock.cpp mapBlock.h pellet.cpp pellet.h player.cpp player.h state.cpp state.h status.cpp status.h texture.cpp texture.h findMobPath.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=CSman

all: $(SOURCES) $(EXECUTABLE)
clean:
	rm -rf *.o
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
