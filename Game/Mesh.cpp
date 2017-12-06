#include "Mesh.h"

Mesh::Mesh(Material * material, Geometry * geometry) {
	this->material = material;
	this->geometry = geometry;
}

void Mesh::Draw() {
	material->UploadAttributes();
	geometry->Draw();
}

Shader* Mesh::GetShader() {
	return material->GetShader();
}

Geometry* Mesh::GetGeometry() {
	return geometry;
}

Texture* Mesh::GetTexture() {
	return material->GetTexture();
}