#pragma once

#include "Util.h"

class Geometry {
protected:
	unsigned int vao;
	float lastUpdateT;

public:
	Geometry() { glGenVertexArrays(1, &vao); }

	virtual void Draw() {}

	virtual void SetState(State s) {}
	virtual bool IncrementFrame() { return false; }

	virtual rectangle GetCollisionBox() {
		return rectangle(vec2(0, 0), vec2(0, 0), vec2(0, 0), vec2(0, 0));
	}
};
