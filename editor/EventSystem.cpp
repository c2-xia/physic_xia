#include "../include.h"
#include <entry/input.h>
#include "Input.h"
#include "EventSystem.h"

EventSystem EventSystem::Instance;

const  entry::MouseState& getMouseState();

void EventSystem::process()
{
	const  entry::MouseState& mState = getMouseState();
	Input::Instance.mouse_x = mState.m_mx;
	Input::Instance.mouse_y = mState.m_my;
	Input::Instance.wheel_value = mState.m_mz;

	if (Input::Instance.wheel_value != nWheelValueCash)
	{
		
		auto it = vecWheelListener.begin();
		for (; it != vecWheelListener.end(); it++)
		{
			(*it)->onWheelChange(Input::Instance.wheel_value - nWheelValueCash);
		}
		nWheelValueCash = Input::Instance.wheel_value;
	}
	if (getMouseState().m_buttons[entry::MouseButton::Enum::Left])
	{
		if (_leftMouse.isMouseDown)
		{
			_leftMouse.DragCheck();
		}
		else
		{
			_leftMouse.onMouseDown();
			_leftMouse.isMouseDown = true;
		}		 
	}
	else
	{
		if (_leftMouse.isMouseDown)
		{
			_leftMouse.onMouseUp();
			_leftMouse.isMouseDown = false;
		}
	}

	if (getMouseState().m_buttons[entry::MouseButton::Enum::Right])
	{
		if (_rightMouse.isMouseDown)
		{
			_rightMouse.DragCheck();
		}
		else
		{
			_rightMouse.onMouseDown();
			_rightMouse.isMouseDown = true;
		}
	}
	else
	{
		if (_rightMouse.isMouseDown)
		{
			_rightMouse.onMouseUp();
			_rightMouse.isMouseDown = false;
		}
	}
}


void MouseEvent::onMouseDown()
{
	posCash.x = Input::Instance.mouse_x;
	posCash.y = Input::Instance.mouse_y;

	auto it = listeners.begin();
	for (; it != listeners.end(); it++)
	{
		(*it)->onMouseDown();
	}

}

void MouseEvent::onMouseUp()
{
	posCash.x = 0;
	posCash.y = 0;
	auto it = listeners.begin();
	for (; it != listeners.end(); it++)
	{
		(*it)->onMouseUp();
	}
}

void MouseEvent::onDrag(Vector2R dPos)
{
	auto it = listeners.begin();
	for (; it != listeners.end(); it++)
	{
		(*it)->onDrag(dPos);
	}
}

void MouseEvent::DragCheck()
{
	if (Input::Instance.mouse_y != posCash.y
	   || Input::Instance.mouse_x != posCash.x )
	{
		 
		Vector2R dPos;
		dPos.x = Input::Instance.mouse_x - posCash.x;
		dPos.y = Input::Instance.mouse_y - posCash.y;
		onDrag(dPos);
		posCash.x = Input::Instance.mouse_x;
		posCash.y = Input::Instance.mouse_y;	 		
	}
}
