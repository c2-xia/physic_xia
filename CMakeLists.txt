cmake_minimum_required (VERSION 3.1) 
set (CMAKE_C_STANDARD 11)
project (physic_xia)

include_directories ("${PROJECT_SOURCE_DIR}/base")
#add_subdirectory (base)
#include_directories ("${PROJECT_SOURCE_DIR}/cal")
#add_subdirectory (cal)
#include_directories ("${PROJECT_SOURCE_DIR}/render")
#add_subdirectory (render)

add_executable(physic_xia
./base/Node.cpp
main.cpp
)
 