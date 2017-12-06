#pragma once

#include"Object.h"

class SpinningObject : public Object {
public:
	SpinningObject(Camera* camera, Mesh* mesh,
		vec2 position, vec2 scaling, float orientation,
		ObjectType type) : Object(camera, mesh, position,
			scaling, orientation, type) {}

	void Rotate(float r) { orientation = r; }
};