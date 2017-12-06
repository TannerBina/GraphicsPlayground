#include "Material.h"

Material::Material(Shader* shader) {
	this->shader = shader;
	this->color = vec4(0, 0, 0, 1);
	this->texture = nullptr;
}

Material::Material(Shader * shader, vec4 color) {
	this->shader = shader;
	this->color = color;
	this->texture = nullptr;
}

Material::Material(Shader * shader, vec4 color, Texture* texture) {
	this->shader = shader;
	this->color = color;
	this->texture = texture;
}

void Material::UploadAttributes() {
	if (texture) {
		shader->UploadSamplerID();
		texture->Bind();
	}
	else
		shader->UploadColor(color);
}

Texture* Material::GetTexture() {
	return texture;
}

Shader* Material::GetShader() {
	return shader;
}