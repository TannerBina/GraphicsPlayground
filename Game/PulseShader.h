#pragma once

#include "ColorShader.h"

class PulseShader : public ColorShader {
public:
	PulseShader() {}
	void UploadColor(vec4 & vertexColor);
};

