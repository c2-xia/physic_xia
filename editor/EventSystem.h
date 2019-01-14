#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

class IMouseEvent
{
public:
	virtual void onMouseDown() {};
	virtual void onMouseUp() {};
	virtual void onDrag(Vector2R dPos) { };
};

class IWheelEvent
{
public:
	virtual void onWheelChange(int value) {}; 
};
class MouseEvent
{
public:
	void onMouseDown();
	void onMouseUp();
	void onDrag(Vector2R dPos);
	void DragCheck();
	bool isMouseDown;
	Vector2R posCash;
 
private:
	std::vector<IMouseEvent*> listeners;
public:
	inline void addListener(IMouseEvent* listener)
	{
		listeners.push_back(listener);
	}
};

class EventSystem
{
public:
	EventSystem():nWheelValueCash(0)
	{

	}
	void process();
	void addLeftMouseLisener(IMouseEvent* listener)
	{
		_leftMouse.addListener(listener);
	}
	void addRightMouseLisener(IMouseEvent* listener)
	{
		_rightMouse.addListener(listener);
	}
	void addWheelListener(IWheelEvent* listener)
	{
		vecWheelListener.push_back(listener);
	}
	static EventSystem Instance;
private:
	MouseEvent _leftMouse;
	MouseEvent _rightMouse;
	std::vector<IWheelEvent*> vecWheelListener;
	int			nWheelValueCash;
};


#endif