#include "TexturedQuad.h"

TexturedQuad::TexturedQuad() {
	glBindVertexArray(vao);
	glGenBuffers(1, &vboTex);

	glBindBuffer(GL_ARRAY_BUFFER, vboTex);
	//tex coords are in normalized space (0 -> 1)
	static float texCoords[] = {0, 1, 1, 1, 0, 0, 1, 0};
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void TexturedQuad::Draw() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisable(GL_BLEND);
}