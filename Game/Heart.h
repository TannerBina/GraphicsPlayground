#pragma once

#include"Geometry.h"

class Heart : public Geometry {
protected:
	unsigned int vbo;

public:
	Heart();

	void Draw();
};
