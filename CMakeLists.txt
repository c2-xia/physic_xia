cmake_minimum_required (VERSION 3.1) 
set (CMAKE_CPP_STANDARD 15)
set (CMAKE_C_STANDARD 15)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
project (physic_xia)

include_directories ("${PROJECT_SOURCE_DIR}/base")
include_directories ("${PROJECT_SOURCE_DIR}/../bgfx/include")
include_directories ("${PROJECT_SOURCE_DIR}/../bimg/include")
include_directories ("${PROJECT_SOURCE_DIR}/../bx/include")
include_directories ("${PROJECT_SOURCE_DIR}/3rdparty/include/bgfx/3rdparty")
include_directories ("${PROJECT_SOURCE_DIR}/3rdparty/include/bgfx/include")
include_directories ("${PROJECT_SOURCE_DIR}/3rdparty/include/bimg/3rdparty")
include_directories ("${PROJECT_SOURCE_DIR}/3rdparty/include/bimg/include")
include_directories ("${PROJECT_SOURCE_DIR}/3rdparty/include/bx/3rdparty")
include_directories ("${PROJECT_SOURCE_DIR}/3rdparty/include/bx/include")
include_directories ("${PROJECT_SOURCE_DIR}/3rdparty/include/common")
include_directories ("${PROJECT_SOURCE_DIR}/3rdparty/include/bx/include/compat/msvc")


link_directories("${PROJECT_SOURCE_DIR}/3rdparty/libs")
link_libraries(bgfxDebug
bimg_decodeDebug
bimgDebug
bxDebug
example-commonDebug
example-glueDebug
psapi
)

ADD_DEFINITIONS(-D_XKEYCHECK_H
-D_HAS_ITERATOR_DEBUGGING=0
)
#add_subdirectory (base)
#include_directories ("${PROJECT_SOURCE_DIR}/cal")
#add_subdirectory (cal)
#include_directories ("${PROJECT_SOURCE_DIR}/render")
#add_subdirectory (render)

add_executable(physic_xia
./base/Node.cpp
./base/BoxNode.cpp
./base/matrix.cpp
./render/cube/cubes.cpp
./render/NodeRender.cpp
./render/NodePushHelper.cpp
main.cpp
)
 