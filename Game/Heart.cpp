#include "Heart.h"

Heart::Heart() {
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	static float vertexCoords[84];
	vertexCoords[0] = 0;
	vertexCoords[1] = 0;
	for (int i = 1; i < 42; i++) {
		double r = .5;
		double t = PI / 2 + (i - 1) * PI / 20;
		double x = (16 * pow(sin(t), 3)) / 16.0;
		double y = (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)) / 16.0;
		vertexCoords[i * 2] = x;
		vertexCoords[i * 2 + 1] = y;
	}


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), vertexCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Heart::Draw() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 42);
}