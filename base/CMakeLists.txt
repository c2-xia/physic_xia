cmake_minimum_required (VERSION 3.1) 

 
add_subdirectory(templeteStructImp)
add_library(base
	BoxNode.cpp
	Node.cpp
	matrix.cpp
	QuaternionHelper.cpp
)