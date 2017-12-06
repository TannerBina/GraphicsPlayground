#include "SpriteSheetQuad.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Util.h"
#include <algorithm>

using namespace std;

SpriteSheetQuad::SpriteSheetQuad(const string& sheetFile)
: collisionBox(vec2(0, 0), vec2(0, 0), vec2(0, 0), vec2(0, 0)){
	currentState = IDLE;
	currentFrame = 0;

	for (int i = 0; i < NONE; i++) {
		stateStarts[i] = 0;
		stateSizes[i] = 0;
	}

	ifstream file(sheetFile);

	int lineNum = -1;
	int numStates = 0;

	int maxHeight = INT_MIN;
	int maxWidth = INT_MIN;

	int sheetHeight = INT_MIN;
	int sheetWidth = INT_MIN;

	int* coords = new int[0];

	float leftPad = 0;
	float rightPad = 0;
	float topPad = 0;
	float bottomPad = 0;

	int offset = 0;

	for (string line; getline(file, line);) {
		stringstream ss(line);

		//data on line -1 is format of
		//leftPad rightPad topPad bottomPad indexOffset
		if (lineNum == -1) {
			ss >> leftPad;
			ss >> rightPad;
			ss >> topPad;
			ss >> bottomPad;

			ss >> offset;

		} if (lineNum == 0) {
			ss >> numStates;
		}
		else if (lineNum <= numStates) {
			string state;
			int numFrames;

			getline(ss, state, '=');
			ss >> numFrames;

			try {
				stateSizes[Util::getState(state)] = numFrames;

				if (lineNum == numStates) {
					for (int i = 0; i < NONE; i++) {
						if (i == 0) {
							stateStarts[i] = 0;
						}
						else {
							stateStarts[i] = stateStarts[i - 1] + stateSizes[i - 1];
						}
					}

					try {
						delete[] coords;
						int size = (stateStarts[NONE - 1] + stateSizes[NONE - 1]) * 8;
						coords = new int[size];
					}
					catch (bad_alloc& ba) {
						cerr << ba.what() << endl;
					}
				}
			}
			catch (exception e){
				//cout << "Could not find state : " << state << endl;
			}
		}
		else {

			string state;
			getline(ss, state, ' ');
			transform(state.begin(), state.end(), state.begin(), ::toupper);

			int frame;
			int leftXCoord;
			int topYCoord;
			int width;
			int height;

			ss >> frame;
			
			char burn;
			ss >> burn;

			ss >> leftXCoord;
			ss >> topYCoord;
			ss >> width;
			ss >> height;

			if (leftXCoord + width > sheetWidth) sheetWidth = leftXCoord + width;
			if (topYCoord + height > sheetHeight) sheetHeight = topYCoord + height;
			if (width > maxWidth) maxWidth = width;
			if (height > maxHeight) maxHeight = height;

			try {
				int start = (stateStarts[Util::getState(state)] + frame-offset) * 8;
				coords[start] = leftXCoord;
				coords[start + 1] = topYCoord + height;
				coords[start + 2] = leftXCoord + width;
				coords[start + 3] = topYCoord + height;
				coords[start + 4] = leftXCoord;
				coords[start + 5] = topYCoord;
				coords[start + 6] = leftXCoord + width;
				coords[start + 7] = topYCoord;
			}
			catch (exception e) {
				//cout << "Cannot find state : " << state;
			}
		}


		lineNum++;
	}

	int size = (stateStarts[NONE - 1] + stateSizes[NONE - 1]) * 8;
	float* texCoords = new float[size];
	float* vertCoords = new float[size];

	for (int i = 0; i < size; i += 2) {
		texCoords[i] = coords[i] / (float)sheetWidth;
		texCoords[i + 1] = (coords[i+1] / float(sheetHeight));
	}

	int max = maxWidth;
	if (maxHeight > max) max = maxHeight;

	for (int i = 0; i < size; i += 8) {
		int width = coords[i + 2] - coords[i];
		int height = coords[i + 1] - coords[i + 5];
		
		float adjustedWidth = width / (float)max;
		float adjustedHeight = height / (float)max;

		float floatHalfWidth = adjustedWidth / (2.0f);

		
		vertCoords[i] = -floatHalfWidth;
		vertCoords[i + 1] = 0;
		vertCoords[i + 2] = floatHalfWidth;
		vertCoords[i + 3] = 0;
		vertCoords[i + 4] = -floatHalfWidth;
		vertCoords[i + 5] = adjustedHeight;
		vertCoords[i + 6] = floatHalfWidth;
		vertCoords[i + 7] = adjustedHeight;
	}

	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(vertCoords), vertCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &vboTex);

	glBindBuffer(GL_ARRAY_BUFFER, vboTex);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	
	topPad /= (float)maxHeight;
	bottomPad /= (float)maxHeight;
	leftPad /= (float)maxWidth;
	rightPad /= (float)maxWidth;

	collisionBox = rectangle(
		vec2(vertCoords[0] + leftPad, vertCoords[1] + bottomPad),
		vec2(vertCoords[2] - rightPad, vertCoords[3] + bottomPad),
		vec2(vertCoords[6] - rightPad, vertCoords[7] - topPad),
		vec2(vertCoords[4] + leftPad, vertCoords[5] - topPad)
	);

	delete[] coords;
	delete[] vertCoords;
	delete[] texCoords;
}

void SpriteSheetQuad::Draw() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(vao);
	int startIndex = (stateStarts[currentState] + currentFrame) * 4;
	glDrawArrays(GL_TRIANGLE_STRIP, startIndex, 4);
	glDisable(GL_BLEND);
}
