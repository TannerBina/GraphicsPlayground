#include"Shader.h"

using namespace std;

Shader::Shader() {
	CompileShader();
}

Shader::~Shader() {
	glDeleteProgram(shaderProgram);
}

void Shader::Run() {
	glUseProgram(shaderProgram);
}