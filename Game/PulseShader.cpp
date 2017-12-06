#include "PulseShader.h"

void PulseShader::UploadColor(vec4 & vertexColor) {
	vec4 newColor(
		vertexColor.v[0] * abs(sin(time)),
		vertexColor.v[1] * abs(sin(time)),
		vertexColor.v[2] * abs(sin(time)),
		vertexColor.v[3]
	);

	int location = glGetUniformLocation(shaderProgram, "vertexColor");
	if (location >= 0) glUniform3fv(location, 1, &newColor.v[0]);
	else printf("uniform vertex color cannot be set\n");
}