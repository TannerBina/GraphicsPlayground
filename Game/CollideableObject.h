#pragma once

#include "Object.h"

class CollideableObject : public Object {
public:
	CollideableObject(Camera* camera, Mesh* mesh, vec2 position, vec2 scaling,
		float orientation, ObjectType type)
		: Object(camera, mesh, position, scaling, orientation, type) {
	}

	bool GetCollision(Object* obj) {
		return GetCollisionBox().collision(obj->GetCollisionBox());
	}
};