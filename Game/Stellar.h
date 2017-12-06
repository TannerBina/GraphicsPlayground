#pragma once
#include "Geometry.h"

class Stellar :public Geometry {
protected:
	unsigned int vbo;

public:
	Stellar();
	void Draw();
};

