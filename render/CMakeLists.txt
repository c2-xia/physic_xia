cmake_minimum_required (VERSION 3.1) 
add_subdirectory(cube)
add_library(render
	NodePushHelper.cpp
	NodeRender.cpp
)