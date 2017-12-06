#include "TextureShader.h"

TextureShader::TextureShader() {
	CompileShader();
}

void TextureShader::CompileShader() {
	// vertex shader in GLSL
	const char *vertexSource = "\n\
			#version 130 \n\
			precision highp float; \n\
			in vec2 vertexPosition;	\n\
			in vec2 vertexTexCoord; \n\
			uniform mat4 M; \n\
			out vec2 texCoord; \n\
			void main() \n\
			{ \n\
				texCoord = vertexTexCoord; \n\
				gl_Position = vec4(vertexPosition.x, \n\
				vertexPosition.y, 0, 1) * M; \n\
			} \n\
		";

	// fragment shader in GLSL
	const char *fragmentSource = "\n\
			#version 130 \n\
			precision highp float; \n\
			uniform sampler2D samplerUnit;\n\
			uniform float windowHeight;\n\
			uniform float windowWidth;\n\
			uniform vec2 center;\n\
			in vec2 texCoord;			// variable input: interpolated from the vertex colors \n\
			out vec4 fragmentColor;		// output that goes to the raster memory as told by glBindFragDataLocation \n\
			\n\
			void main() \n\
			{ \n\
				float lD = 1.5;\n\
				float x = ((gl_FragCoord.x / windowWidth)-.5)*2;\n\
				float y = ((gl_FragCoord.y / windowHeight)-.5) *2;\n\
				y = y * windowHeight/windowWidth;\n\
				x = (x - center.x);\n\
				y = (y - center.y);\n\
				float z = gl_FragCoord.z;\n\
				float adjustValue = max(-(x*x + y*y) * lD, -.9);\n\
				float redFilter = -abs(sin(x * y));\n\
				float greenFilter = -abs(sin(x));\n\
				float blueFilter = -abs(sin(y));\n\
				vec4 filter = vec4(redFilter, greenFilter, blueFilter, 0);\n\
				vec4 textureColor = texture(samplerUnit, texCoord); // extend RGB to RGBA \n\
				vec4 adjust = vec4(adjustValue * textureColor.x, adjustValue * textureColor.y, adjustValue * textureColor.z, 0);\n\
				fragmentColor = textureColor + adjust + (filter * .2);\n\
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

void TextureShader::UploadSamplerID() {
	int samplerUnit = 0;
	int location = glGetUniformLocation(shaderProgram,
		"samplerUnit");
	glUniform1i(location, samplerUnit);
	glActiveTexture(GL_TEXTURE0 + samplerUnit);
}

void TextureShader::UploadWindowSpecs(float windowHeight, float windowWidth, vec2 center) {
	int location1 = glGetUniformLocation(shaderProgram, "windowHeight");
	int location2 = glGetUniformLocation(shaderProgram, "windowWidth");
	int location3 = glGetUniformLocation(shaderProgram, "center");
	glUniform1f(location1, windowHeight);
	glUniform1f(location2, windowWidth);
	glUniform2f(location3, center.x, center.y);
}