#include "Object.h"

void Object::syncTransform()
{

	float conv = M_PI / 180.0f;
	float radx = rot[0]*conv , rady = rot[1]*conv , radz = rot[2]*conv ;
	float cx = std::cos(radx), sx = std::sin(radx);
	float cy = std::cos(rady), sy = std::sin(rady);
	float cz = std::cos(radz), sz = std::sin(radz);

	transform[0][0] = (cy * cz) * sca[0];							transform[0][1] = (-sz * cy) * sca[1];								transform[0][2] = sy * sca[2];					transform[0][3] = pos[0];
	transform[1][0] = (cx * sz + cz * sy * sx) * sca[0];			transform[1][1] = (cz * cx - sx * sz * sy) * sca[1];				transform[1][2] = -cy * sx * sca[2];			transform[1][3] = pos[1];
	transform[2][0] = (sz * sx - cx * cz * sy) * sca[0];			transform[2][1] = (cz * sx + sz * sy * cx) * sca[1];				transform[2][2] = cx * cy * sca[2];				transform[2][3] = pos[2];
	transform[3][0] = 0;											transform[3][1] = 0;												transform[3][2] = 0;							transform[3][3] = 1;

}

Object::Object(Mesh& mesh, Texture& tex) : mesh(mesh), tex(tex) 
{
	for (int i = 0; i < 3; i++)
	{
		pos[i] = 0.0f;
		rot[i] = 0.0f;
		sca[i] = 1.0f;
	}
	syncTransform();
}

Object::~Object()
{
}

Object::Object(Object& g) : mesh(g.mesh), tex(g.tex)
{
	pos = g.pos;
	rot = g.rot;
	sca = g.sca;
	transform = g.transform;
}

Object::Object(Object&& g) : mesh(g.mesh), tex(g.tex)
{
	pos = std::move(g.pos);
	rot = std::move(g.rot);
	sca = std::move(g.sca);
	transform = std::move(g.transform);
}

void Object::bind()
{
	mesh.bind();
}

void Object::unbind()
{
	mesh.unbind();
}

Texture& Object::getTexture()
{
	return tex;
}

Mesh& Object::getMesh()
{
	return mesh;
}

int Object::size()
{
	return mesh.indicesSize();
}

unsigned int Object::getTextureId()
{
	return tex.getTextureId();
}

void Object::translate(float dx, float dy, float dz)
{
	pos[0] += dx;	pos[1] += dy;	pos[2] += dz;
	for (int i = 0; i < 3; i++)
		transform[i][3] = pos[i];
}

void Object::rotate(float dx, float dy, float dz)
{
	rot[0] += dx;	rot[1] += dy;	rot[2] += dz;
	for (int i = 0; i < 3; i++)
	{
		if (rot[i] > 360.0f)
			rot[i] -= 360.0f;
	}
	syncTransform();
}

void Object::scale(float dx, float dy, float dz)
{
	sca[0] += dx;	sca[1] += dy;	sca[2] += dz;
	syncTransform();
}

void Object::setPosition(float x, float y, float z)
{
	pos[0] = x;	 pos[1] = y;	pos[2] = z;
	for (int i = 0; i < 3; i++)
		transform[i][3] = pos[i];
}

void Object::setRotation(float x, float y, float z)
{
	rot[0] = x;	rot[1] = y;	rot[2] = z;
	syncTransform();
}

void Object::setScale(float x, float y, float z)
{
	sca[0] = x;	sca[1] = y;	 sca[2] = z;
	syncTransform();
}

Mat4& Object::getTransform()
{
	return transform;
}
