#pragma once

#include "CollideableObject.h"

class MoveableObject : public CollideableObject{
protected:
	vec2 velocity;
	vec2 originalScaling;
	float jumpStrength;
	int numJumps = 2;

public:
	MoveableObject(Camera* camera, Mesh* mesh, vec2 position, vec2 scaling,
		float orientation, ObjectType type) 
		: CollideableObject(camera, mesh, position, scaling, orientation, type),
		velocity(0, 0){
	
		originalScaling = scaling;
		jumpStrength = 1.5;
	}

	bool Moveable() { return true; }

	void Move(float dt, std::vector<Object*> tiles) {
		if (velocity.x < 0) {
			scaling.x = -originalScaling.x;
		}
		else if (velocity.x > 0) {
			scaling.x = originalScaling.x;
		}

		vec2 movement = velocity * dt;
		
		position = position + vec2(movement.x, 0);

		for (Object* b : tiles) {
			if (GetCollision(b)) {
				position = position - vec2(movement.x, 0);
				velocity.x = 0;
				break;
			}
		}

		position = position + vec2(0, movement.y);

		for (Object* b : tiles) {
			if (GetCollision(b)) {
				position = position - vec2(0, movement.y);
				if (velocity.y < 0) {
					numJumps = 2;
					jumping = false;
				}
				velocity.y = 0;
				break;
			}
		}
	}

	void IncreaseVelocity(vec2 addedVelocity) {
		velocity = velocity + addedVelocity;
	}

	void SetVelocity(vec2 velocity) {
		this->velocity = velocity;
	}

	vec2 GetVelocity() { return velocity; }

	void ApplyGravity(float dt) {
		if (velocity.y < GRAVITY_MAX) {
			velocity.y -= GRAVITY_ACCELERATION * dt;
		}
		else {
			velocity.y = -GRAVITY_MAX;
		}
	}

	void Jump() {
		if (numJumps > 0 && velocity.y <= jumpStrength/2.0) {
			velocity.y = jumpStrength;
			numJumps--;
			jumping = true;
		}
	}
};