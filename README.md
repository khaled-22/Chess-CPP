# Chess-game in c++
A chess game inspired in c++

# Libaries 
- Docs:https://www.sfml-dev.org/documentation/2.6.1-fr/
- vcpkg for dependency management, specifically for SFML
- RAII for resource management to ensure clean and efficient use of resources.

## Prerequisites

- CMake (version 3.10 or higher)
- vcpkg for dependency management
- SFML (managed by vcpkg)

# How to Install from zero 
1. git clone https://github.com/khaled-22/Chess-CPP.git
2. cd Chess-CPP
3. Follow the instructions on the vcpkg GitHub page to install vcpkg.
- vcpkg install sfml
4. Configure and build the project with CMake
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build .
