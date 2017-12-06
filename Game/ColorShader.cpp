#include "ColorShader.h"

ColorShader::ColorShader() {
	CompileShader();
}

void ColorShader::UploadColor(vec4 & vertexColor) {
	int location = glGetUniformLocation(shaderProgram, "vertexColor");
	if (location >= 0) glUniform3fv(location, 1, &vertexColor.v[0]);
	else printf("uniform vertex color cannot be set\n");
}

void ColorShader::CompileShader() {
	// vertex shader in GLSL
	const char *vertexSource = "\n\
			#version 130 \n\
			precision highp float; \n\
			in vec2 vertexPosition;	\n\
			out vec3 color; \n\
			uniform mat4 M; \n\
			uniform vec3 vertexColor; \n\
			void main() \n\
			{ \n\
				color = vertexColor; \n\
				gl_Position = vec4(vertexPosition.x, \n\
				vertexPosition.y, 0, 1) * M; \n\
			} \n\
		";

	// fragment shader in GLSL
	const char *fragmentSource = "\n\
			#version 130 \n\
			precision highp float; \n\
			\n\
			in vec3 color;			// variable input: interpolated from the vertex colors \n\
			out vec4 fragmentColor;		// output that goes to the raster memory as told by glBindFragDataLocation \n\
			\n\
			void main() \n\
			{ \n\
				fragmentColor = vec4(color, 1); // extend RGB to RGBA \n\
			} \n\
		";

	// create vertex shader from string
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (!vertexShader) { printf("Error in vertex shader creation\n"); exit(1); }

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	Util::checkShader(vertexShader, "Vertex shader error");

	// create fragment shader from string
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragmentShader) { printf("Error in fragment shader creation\n"); exit(1); }

	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	Util::checkShader(fragmentShader, "Fragment shader error");

	// attach shaders to a single program
	shaderProgram = glCreateProgram();
	if (!shaderProgram) { printf("Error in shader program creation\n"); exit(1); }

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// connect Attrib Array to input variables of the vertex shader
	glBindAttribLocation(shaderProgram, 0, "vertexPosition"); // vertexPosition gets values from Attrib Array 0

															  // connect the fragmentColor to the frame buffer memory
	glBindFragDataLocation(shaderProgram, 0, "fragmentColor"); // fragmentColor goes to the frame buffer memory

															   // program packaging
	glLinkProgram(shaderProgram);
	Util::checkLinking(shaderProgram);
}