# Variables for source file, output, and compiler options
SRC = /home/darkemperor/aathi/my-learnig-path-/TIC_TAC_TOE/usr/share/doc/src/eg.c
OUTPUT = tic_tac_toe

# Compiler flags for Windows and Linux
SDL2_CFLAGS = -I/usr/include/SDL2
SDL2_LIBS_LINUX = -lSDL2 -lwayland-client -lSDL2_mixer
SDL2_LIBS_WINDOWS = -lSDL2 -lSDL2main -mwindows -lSDL2_mixer

# Determine the platform using uname
UNAME := $(shell uname)

# Default target (decides which platform to compile for)
all: detect-os

# Target for Linux
linux:
	@echo "Compiling for Linux..."
	gcc -o $(OUTPUT) $(SRC) $(SDL2_CFLAGS) $(SDL2_LIBS_LINUX)
	@echo "Done. You can run it with: ./$(OUTPUT)"

# Target for Windows
windows:
	@echo "Compiling for Windows..."
	x86_64-w64-mingw32-gcc -o $(OUTPUT).exe $(SRC) $(SDL2_CFLAGS) $(SDL2_LIBS_WINDOWS) -Dmain=SDL_main
	@echo "Done. You can run the executable: $(OUTPUT).exe"

# Detect the operating system and choose the appropriate target
detect-os:
ifeq ($(UNAME), Linux)
	$(MAKE) linux
else
	$(MAKE) windows
endif

# Clean target to remove generated files
clean:
	@echo "Cleaning up..."
	rm -f $(OUTPUT) $(OUTPUT).exe
	@echo "Done."
