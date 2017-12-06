#pragma once

#include "Util.h"
#include "Shader.h"

class Light {
	vec2 position;

public:
	Light(vec2 position)
	:position(position) {
	}

	void SetPosition(vec2 newPos) {
		position = newPos;
	}

	void UploadAttributes(Shader* shader) {
	}
};
