#pragma once

#include "Quad.h"

class SpriteSheetQuad : public Geometry{
protected:
	unsigned int vboTex;
	unsigned int vbo;

	State currentState;
	int currentFrame;

	int stateStarts[NONE];
	int stateSizes[NONE];

	rectangle collisionBox;

public:
	SpriteSheetQuad(const std::string& sheetFile);
	void Draw();
	void SetState(State s) { 
		currentState = s;
		currentFrame = 0;
	}
	//return true if incrementing the frame, finishes the animation
	bool IncrementFrame()
	{
		int initFrame = currentFrame;
		currentFrame = (currentFrame + 1) % stateSizes[currentState];
		if (currentFrame == 0 && initFrame != 0) {
			return true;
		}
		return false;
	}

	rectangle GetCollisionBox() {
		return collisionBox;
	}
};