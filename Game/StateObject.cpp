#include "StateObject.h"

StateObject::StateObject(Camera* camera, Mesh* mesh,
	vec2 position, vec2 scaling, float orientation,
	ObjectType type) : MoveableObject(camera, mesh, position, scaling,
		orientation, type), stateHandler(this) {}

void StateObject::Animate(float t) {
	stateHandler.Update(t);
}