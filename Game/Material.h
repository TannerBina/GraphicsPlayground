#pragma once

#include "Shader.h"
#include "Texture.h"

class Material {
	Shader* shader;

	vec4 color;

protected:
	Texture* texture;

public:
	Material(Shader* shader);
	Material(Shader* shader, vec4 color);
	Material(Shader* shader, vec4 color, Texture* texture);

	void UploadAttributes();
	Shader* GetShader();
	Texture* GetTexture();
};
