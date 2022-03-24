#ifndef CAM_ERA
#define CAM_ERA

#include "Mathril.h"

class Camera
{
private:


public:

	Quat spin;
	Vec3 position;

	Camera();
	void setPosition(float x, float y, float z);
	void rotate(float x, float y, float z);
	void translate(float forward, float strafe);


};
#endif