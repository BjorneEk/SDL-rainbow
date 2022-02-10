TARGET = sdl-rainbow

CC = g++

INCLUDE_DIR = src/include
CFLAGS = -F /Library/Frameworks -framework SDL2 -Wall -I$(INCLUDE_DIR)
C_SOURCES = $(wildcard src/*.cpp src/lib/*.cpp )
DEPS = $(wildcard $(INCLUDE_DIR)/*.hpp src/*.h)
OBJ = ${C_SOURCES:.cpp=.o}

# First rule is the one executed when no parameters are fed to the Makefile


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) src/*.bin src/*.o src/*.dis src/*.elf
	$(RM) lib/*.
