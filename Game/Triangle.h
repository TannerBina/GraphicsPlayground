#pragma once

#include "Geometry.h"

class Triangle : public Geometry {
protected:
	unsigned int vbo;

public:
	Triangle();
	void Draw();
};
