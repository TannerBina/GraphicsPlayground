#pragma once

#include "Util.h"

class Shader {
protected:
	unsigned int shaderProgram;
	float time;

public:
	Shader();
	~Shader();
	
	void Run();


	virtual void CompileShader() {}

	virtual void UploadTime(float t) { time = t; }

	virtual void UploadColor(vec4 & vertexColor) {}

	virtual void UploadM(mat4& M){
		int location = glGetUniformLocation(shaderProgram, "M");
		if (location >= 0) glUniformMatrix4fv(location, 1, GL_TRUE, M);
		else printf("uniform M cannot be set\n");
	}

	virtual void UploadSamplerID() {}

	virtual void UploadSubTextureID(int numRows, int numCols, int subTextureID) {}

	virtual void UploadWindowSpecs(float windowHeight, float windowWidth, vec2 center) {}
};