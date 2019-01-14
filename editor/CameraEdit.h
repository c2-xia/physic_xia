#ifndef CAMERA_EDIT_H
#define CAMERA_EDIT_H

class CameraEdit:public  IMouseEvent,public IWheelEvent
{
public:
	virtual void onDrag(Vector2R dPos);
	virtual void onWheelChange(int value);
	Camera*  _pCamera;
};


#endif //CAMERA_EDIT_H