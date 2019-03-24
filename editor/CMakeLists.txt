cmake_minimum_required (VERSION 3.1) 
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
add_library(editor
	Input.cpp
	EventSystem.cpp
	CameraEdit.cpp
	WorldDraw.cpp
	EditorBoxCollider.cpp
${CURRENT_HEADERS}
)