#pragma once

#include "MoveableObject.h"
#include "StateHandler.h"

class StateObject : public MoveableObject {
	StateHandler stateHandler;

public:
	StateObject(Camera* camera, Mesh* mesh,
		vec2 position, vec2 scaling, float orientation,
		ObjectType type);

	void Animate(float t);

	void Jump() {
		if (numJumps > 0 && velocity.y <= jumpStrength / 2.0
			&& !stateHandler.InTemporaryState()) {
			velocity.y = jumpStrength;
			numJumps--;
			jumping = true;
			stateHandler.ForceState(JUMP);
		}
	}
};