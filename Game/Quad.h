#pragma once

#include"Geometry.h"

class Quad : public Geometry {
protected:
	unsigned int vbo;
public:
	Quad();
	void Draw();
	rectangle GetCollisionBox() {
		return rectangle(
			vec2(-.5, 1),
			vec2(-.5, 0),
			vec2(.5, 0),
			vec2(.5, 1)
		);
	}
};
