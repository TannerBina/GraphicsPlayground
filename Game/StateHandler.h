#pragma once

class StateObject;

#include "Util.h"
#include "Object.h"

class StateHandler {
	float stateFrameTime[NONE];
	bool temporaryState[NONE];
	State current;
	Object* object;
	float lastUpdateT;

	void InferState();

public:
	StateHandler() {}
	StateHandler(Object* object);

	void Update(float t);
	void ForceState(State s);

	bool InTemporaryState() { return temporaryState[current]; }
	State GetState() { return current; }
};