#include "Camera.h"

Camera::Camera()
{
	spin[0] = 1;
	spin[1] = 0;
	spin[2] = 0;
	spin[3] = 0;
}

void Camera::setPosition(float x, float y, float z)
{
	position[0] = x; position[1] = y; position[2] = z;
}

void Camera::rotate(float x, float y, float z)
{
	float rad = PI / 180.0f;
	float radx = x / 2 * rad, rady = y / 2 * rad, radz = z / 2 * rad;
	float cx = std::cos(radx), sx = std::sin(radx);
	float cy = std::cos(rady), sy = std::sin(rady);
	float cz = std::cos(radz), sz = std::sin(radz);

    spin = Quat(cy, 0, sy, 0) * spin * Quat(cx, sx, 0, 0) * Quat(cz, 0, 0, sz);
}

void Camera::translate(float forward, float strafe)
{
	Quat mv(0.0f, strafe, 0.0f, -forward);
	mv = spin * mv * (~spin);
	position = position + Vec3(mv[1], mv[2], mv[3]);
}
