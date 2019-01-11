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

ADD_DEFINITIONS(
-D__STDC_LIMIT_MACROS
-D__STDC_FORMAT_MACROS
-D__STDC_CONSTANT_MACROS
-D_HAS_ITERATOR_DEBUGGING=0
-D_DEBUG
-DWIN32
-D_WIN32
-D_HAS_EXCEPTIONS=0
-D_HAS_ITERATOR_DEBUGGING=0
-D_SCL_SECURE=0
-D_SECURE_SCL=0
-D_SCL_SECURE_NO_WARNINGS
-D_CRT_SECURE_NO_WARNINGS
-D_CRT_SECURE_NO_DEPRECATE
 /Zi
)

include_directories ("${PROJECT_SOURCE_DIR}/base")
add_subdirectory (base)
include_directories ("${PROJECT_SOURCE_DIR}/cal")
add_subdirectory (cal)
include_directories ("${PROJECT_SOURCE_DIR}/render")
add_subdirectory (render)
 
include_directories ("${PROJECT_SOURCE_DIR}/runtime")
add_subdirectory (runtime)


add_executable(physic_xia
main.cpp
)
target_link_libraries(physic_xia render base cube templeteStructImp runtime)
 