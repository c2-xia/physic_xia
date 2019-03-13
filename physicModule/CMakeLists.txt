cmake_minimum_required (VERSION 3.1) 
add_subdirectory(simulation)
add_library(physicModule
	PhysicsDefine.cpp
	rigidbody.cpp
	ColliderManager.cpp
)