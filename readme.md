# Tic Tac Toe Game in C

## Introduction

A simple two-player Tic Tac Toe game built with C, using SDL2 for graphics and Wayland for display server support (Linux). Players take turns marking X or O on a 3x3 grid, aiming for three in a row to win.

## Prerequisites

- **SDL2**: Download from [https://www.libsdl.org/download-2.0.php](https://www.libsdl.org/download-2.0.php)
- **SDL2_ttf**: Download from [https://github.com/libsdl-org/SDL_ttf/releases](https://github.com/libsdl-org/SDL_ttf/releases)
- **Wayland**: Install from [https://wayland.freedesktop.org/](https://wayland.freedesktop.org/) (Linux only)
- **Inno Setup**: Download from [https://jrsoftware.org/isdl.php](https://jrsoftware.org/isdl.php) (Windows only)

## Installation

### Linux
1. Install dependencies:
   ```bash
   sudo apt update
   sudo apt install libsdl2-dev libwayland-dev libsdl2-ttf-dev make
   ```
2. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-name>
   ```
3. Build and install:
   ```bash
   ./build.sh
   sudo dpkg -i <package-name>.deb
   ```

### Windows
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-name>
   ```
2. Download and install [Inno Setup](https://jrsoftware.org/isdl.php).
3. Run the installer script:
   ```bash
   cd src
   iscc project.iss
   ```
4. Locate the generated `.exe` in the `Windows/` directory and run it to install and play.

## Contributing
For development or contributions, see [CONTRIBUTING.md](./CONTRIBUTING.md).

## How to Play
1. Launch the game:
   - Linux: Run the installed application.
   - Windows: Run the installed `.exe`.
2. Players alternate placing X or O on the 3x3 grid.
3. Win by aligning three marks horizontally, vertically, or diagonally.
4. Game ends in a draw if all squares are filled without a winner.

## Features
- Simple graphical interface using SDL2.
- Two-player mode.
- Reset option to start a new game.

## Troubleshooting
- Ensure all dependencies (SDL2, SDL2_ttf, Wayland for Linux, Inno Setup for Windows) are installed.
- Check terminal for errors during compilation or installation.
- Verify library paths for linking issues.

## License
This project is licensed under the GNU General Public License v3.0 - see the [COPYING](./COPYING) file for details.

## Acknowledgments
- SDL2 community for their resources.
- Wayland documentation for display server support.
- Inno Setup for Windows installer support.
