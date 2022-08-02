#ifndef H_VASTU_H
#define H_VASTU_H

#include "Mesh.h"
#include "Mathril.h"
#include "Texture.h"

class Object
{
private:
	Vec3 pos,rot,sca;
	Mat4 transform;
	Mesh& mesh;
	Texture& tex;
	void syncTransform();

public:
	Object(Mesh& mesh, Texture& tex);
	~Object();
	Object(Object&);
	Object(Object&&);
	void bind();
	void unbind();
	int size();
	unsigned int getTextureId();

	void translate(float dx, float dy, float dz);
	void rotate(float dx, float dy, float dz);
	void scale(float dx, float dy, float dz);

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

	Mat4& getTransform();

	Texture& getTexture();
	Mesh& getMesh();
};


#endif