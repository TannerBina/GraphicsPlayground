#pragma once

#include "Shader.h"

class TextureShader : public Shader {

public:
	TextureShader();

	void CompileShader();
	void UploadSamplerID();
	void UploadWindowSpecs(float windowHeight, float windowWidth, vec2 center);
};

