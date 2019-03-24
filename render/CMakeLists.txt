cmake_minimum_required (VERSION 3.1) 
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
add_library(render
	NodePushHelper.cpp
	NodeRender.cpp
Camera.cpp
cube/cubes.cpp
${CURRENT_HEADERS}
)