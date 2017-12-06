#pragma once

#include"Quad.h"

class TexturedQuad : public Quad {
protected:
	unsigned int vboTex;

public:
	TexturedQuad();
	void Draw();
};
