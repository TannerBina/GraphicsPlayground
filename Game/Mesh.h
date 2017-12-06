#pragma once
#include"Geometry.h"
#include"Material.h"

class Mesh {
	Material* material;
	Geometry* geometry;

public:
	Mesh(Material* material, Geometry* geometry);
	void Draw();
	Shader* GetShader();
	Geometry* GetGeometry();
	Texture* GetTexture();
	Material* GetMaterial() { return material; }
};
