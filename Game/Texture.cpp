#include "Texture.h"

Texture::Texture(const std::string & inputFileName) {
	unsigned char* data;
	int width; int height; int nComponents = 4;

	data = stbi_load(inputFileName.c_str(), &width,
		&height, &nComponents, 0);

	if (data == NULL) return;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
		height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);

	delete data;
	numRows = 1;
	numCols = 1;
	animationTime = -1;
}

Texture::Texture(const std::string & inputFileName, int numRows,
	int numCols, float animationTime) {
	unsigned char* data;
	int width; int height; int nComponents = 4;

	data = stbi_load(inputFileName.c_str(), &width,
		&height, &nComponents, 0);

	if (data == NULL) return;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
		height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);

	delete data;

	this->numRows = numRows;
	this->numCols = numCols;
	this->animationTime = animationTime;
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, textureId);
}