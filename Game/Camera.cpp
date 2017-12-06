#include "Camera.h"

Camera::Camera() {
	center = vec2(0, 0);
	hx = 1;
	hy = 1;
	orientation = 0;
}

Camera::Camera(vec2 center, float hx, float hy) {
	this->center = center;
	this->hx = hx;
	this->hy = hy;
}

mat4 Camera::GetViewTransformationMatrix() {
	mat4 T(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-center.x, -center.y, 0, 1);

	mat4 R(cos(orientation), sin(orientation), 0, 0,
		-sin(orientation), cos(orientation), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	mat4 S(1 / hx, 0, 0, 0,
		0, 1 / hy, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	return T*R*S;
}

mat4 Camera::GetInverseViewTransformationMatrix() {
	return GetViewTransformationMatrix().invert();
}

void Camera::SetAspectRatio(int height, int width) {
	hx = (float)width / (float)height;
	hy = 1;
}

void Camera::SetPosition(vec2 pos) {
	center = pos;
	if (background) {
		vec2 bgPos(pos.x, pos.y - 1);
		background->SetPos(bgPos);
	}
}

void Camera::Rotate(float r) {
	orientation = r;
	if (background) {
		background->SetOrientation(r);
	}
}

void Camera::BindBackground(Object* bg) {
	background = bg;
}
