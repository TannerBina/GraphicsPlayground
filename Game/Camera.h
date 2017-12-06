#pragma once

class Object;

#include "Util.h"
#include "Object.h"

class Camera {
private:
	vec2 center;
	float hx;
	float hy;
	float orientation;

	Object* background;

public:
	Camera();
	Camera(vec2 center, float hx, float hy);
	vec2 GetPosition() { return center; }
	void SetPosition(vec2 pos);
	void Rotate(float r);
	mat4 GetViewTransformationMatrix();
	mat4 GetInverseViewTransformationMatrix();

	//TODO FIX THIS
	void SetAspectRatio(int height, int width);

	void BindBackground(Object* bg);
};
