#pragma once
#include "Shader.h"

class ColorShader : public Shader {
public:
	ColorShader();
	
	void UploadColor(vec4 & vertexColor);
	void CompileShader();
};
