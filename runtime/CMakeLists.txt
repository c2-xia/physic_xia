cmake_minimum_required (VERSION 3.1) 
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
add_library(runtime
	GlobalValues.cpp
${CURRENT_HEADERS}
)