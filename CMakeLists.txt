# CMakeList.txt : CMake project for Chess_4_cmake_vcpkg, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("Chess_4_cmake_vcpkg")

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(SFML_DIR "C:/vcpkg/packages/sfml_x64-windows/lib")
include_directories(${SFML_INCLUDE_DIR})

find_package(SFML 2.6 REQUIRED COMPONENTS system window graphics)


# Add source to this project's executable.
add_executable (Chess_4_cmake_vcpkg 
	"main.cpp" 
	"Chess_4_cmake_vcpkg.h" 
	"Controller/ChessGame.h"
	"Controller/ChessGame.cpp"
)
target_link_libraries(Chess_4_cmake_vcpkg PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
include_directories(${PROJECT_SOURCE_DIR}/Controller)
#source_group(TREE ${PROJECT_SOURCE_DIR}/Controller PREFIX "Header Files")