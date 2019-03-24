cmake_minimum_required (VERSION 3.1) 

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
add_library(base
	BoxNode.cpp
	Node.cpp
	matrix.cpp
	QuaternionHelper.cpp
	SpaceRepresent.cpp
	templeteStructImp/Vector3
${CURRENT_HEADERS}
)