#pragma once

class Camera;

#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

class Object {
protected:
	Shader* shader;
	Mesh* mesh;
	vec2 position;
	vec2 scaling;
	float orientation;
	ObjectType type;
	Camera* camera;

	bool jumping;

public:
	Object() {}
	Object(Camera* camera, Mesh* mesh, 
		vec2 position, vec2 scaling, float orientation,
		ObjectType type);

	vec2 GetScaling() { return scaling; }
	vec2 GetPosition() { return position; }
	ObjectType GetType() { return type; }
	Geometry* GetGeometry() { return mesh->GetGeometry(); }

	void SetPos(vec2 pos) { position = pos; }
	void SetScale(vec2 scale) { scaling = scale; }
	void SetOrientation(float o) { orientation = o; }
	
	bool IsJumping() { return jumping; }

	Shader* GetShader() { return shader; }

	virtual void Rotate(float r) {}
	virtual void Animate(float t) {}
	virtual void Move(float dt, std::vector<Object*> tiles){}
	virtual void Jump() {}
	virtual void IncreaseVelocity(vec2 addedVelocity) {}
	virtual void SetVelocity(vec2 velocity) {}
	virtual vec2 GetVelocity() { return vec2(0, 0); }
	virtual void ApplyGravity(float dt){}

	rectangle GetCollisionBox();
	virtual bool GetCollision(Object* obj) { return false; }
	virtual bool Moveable() { return false; }

	void UploadAttributes();
	void Draw();

};
