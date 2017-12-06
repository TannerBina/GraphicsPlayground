#include "Stellar.h"

Stellar::Stellar() {
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	static float vertexCoords[24];
	vertexCoords[0] = 0;
	vertexCoords[1] = 0;
	for (int i = 1; i < 12; i++) {
		double r = 1;

		if (i % 2 == 1) r = .4;

		double angle = (90 + (i * 36)) * PI / 180;
		vertexCoords[i * 2] = r*cos(angle);
		vertexCoords[i * 2 + 1] = r*sin(angle);
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), vertexCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Stellar::Draw() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 12);
}