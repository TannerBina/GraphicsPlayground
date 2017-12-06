#include "StateHandler.h"

StateHandler::StateHandler(Object* object) {
	this->object = object;
	lastUpdateT = -1;

	temporaryState[JUMPATTACK] = true;
	temporaryState[ATTACK] = true;
	temporaryState[RUNSHOOT] = true;
	temporaryState[SHOOT] = true;
	temporaryState[SLIDE] = true;

	for (int i = 0; i < NONE; i++) {
		stateFrameTime[i] = .1;
	}

	switch (object->GetType()) {
	case ROBOT:
		stateFrameTime[JUMP] = .15;
		break;
	default:
		break;
	}
}

void StateHandler::InferState() {
	State correctState = IDLE;

	vec2 velocity = object->GetVelocity();
	
	if (abs(velocity.y) > FALLING_CUTOFF || velocity.y > 0
		|| object->IsJumping()) {
		correctState = JUMP;
	}
	else if (abs(velocity.x) > 0) {
		correctState = RUN;
	}

	if (correctState != current) {
		object->GetGeometry()->SetState(correctState);
		current = correctState;
	}
}

void StateHandler::Update(float t) {
	//if not currently a temporary state, make sure 
	//to set the correct state using InferState
	if (!temporaryState[current]) {
		InferState();
	}

	if (lastUpdateT == -1) {
		lastUpdateT = t;
		return;
	}

	if (t - lastUpdateT > stateFrameTime[current]) {
		lastUpdateT = t;
		bool animFinished = object->GetGeometry()->IncrementFrame();
		if (animFinished && temporaryState[current]) {
			InferState();
		}
	}
}

void StateHandler::ForceState(State s) {
	if (!temporaryState[current]) object->GetGeometry()->SetState(s);
}