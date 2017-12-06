#include "Object.h"

Object::Object(Camera* camera, Mesh* mesh, vec2 position, vec2 scaling, float orientation, ObjectType type) {
	this->camera = camera;
	this->shader = mesh->GetShader();
	this->mesh = mesh;
	this->position = position;
	this->scaling = scaling;
	this->orientation = orientation;
	this->type = type;
}

rectangle Object::GetCollisionBox() {
	mat4 S(scaling.x, 0, 0, 0,
		0, scaling.y, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	mat4 R(cos(orientation), sin(orientation), 0, 0,
		-sin(orientation), cos(orientation), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	mat4 T(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		position.x, position.y, 0, 1);

	mat4 M = S*R*T;

	return mesh->GetGeometry()->GetCollisionBox() * M;
}

void Object::UploadAttributes() {
	mat4 S(scaling.x, 0, 0, 0,
		0, scaling.y, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	mat4 R(cos(orientation), sin(orientation), 0, 0,
		-sin(orientation), cos(orientation), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	mat4 T(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		position.x, position.y, 0, 1);

	mat4 M = S*R*T;

	shader->UploadM(M * camera->GetViewTransformationMatrix());
}

void Object::Draw() {
	shader->Run();
	shader->UploadWindowSpecs(WINDOW_HEIGHT, WINDOW_WIDTH, LIGHT_CENTER);
	UploadAttributes();
	mesh->Draw();
}