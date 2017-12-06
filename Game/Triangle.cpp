#include "Triangle.h"

Triangle::Triangle() {
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	static float vertexCoords[] = { -1, -1, 1, -1, -1, 1 };

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertexCoords),
		vertexCoords,
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0,
		2, GL_FLOAT,
		GL_FALSE,
		0, NULL);
}

void Triangle::Draw() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}