#ifndef INPUT_H
#define INPUT_H

class Input
{
public:
	int mouse_x;
	int mouse_y;
	int wheel_value;


	static Input Instance;
};


#endif