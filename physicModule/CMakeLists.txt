cmake_minimum_required (VERSION 3.1) 
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
add_library(physicModule
	PhysicsDefine.cpp
	rigidbody.cpp
	ColliderManager.cpp
	simulation/BhvNode.cpp
	simulation/M_Simulation.cpp
${CURRENT_HEADERS}
)