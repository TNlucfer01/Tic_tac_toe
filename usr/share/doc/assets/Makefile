# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I/usr/include/SDL2
LDFLAGS = -lSDL2 -lwayland-client

# Source files and executable name
SRC =/home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/usr/share/doc/src/eg.c
EXEC = tic_tac_toe

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(LDFLAGS)

# Clean up build files
clean:
	rm -f $(EXEC)
