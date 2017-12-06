#pragma once

#include"Camera.h"
#include"Shader.h"
#include"Texture.h"
#include"Material.h"
#include"Mesh.h"
#include"ColorShader.h"
#include"TextureShader.h"
#include"PulseShader.h"
#include"Triangle.h"
#include"Quad.h"
#include"Stellar.h"
#include"Heart.h"
#include"TexturedQuad.h"
#include"Object.h"
#include"SpinningObject.h"
#include"SpriteSheetQuad.h"

enum TileSetType {
	TIL_MACHINE
};

class ObjectBuilder {
	Camera* camera;

	enum ShaderType
	{
		SHA_TEXTURE, SHA_COLOR
	};
	std::vector<Shader*> shaders;

	enum TextureType {
		TEX_RUNNING_GIRL, TEX_ROBOT, TEX_BACKGROUND
	};
	std::vector<Texture*> textures;

	enum MaterialType {
		MAT_RUNNING_GIRL, MAT_ROBOT, MAT_RED, MAT_BACKGROUND
	};
	std::vector<Material*> materials;

	enum GeometryType {
		GEO_TEXTURED_QUAD, GEO_SS_QUAD, GEO_QUAD
	};
	std::vector<Geometry*> geometries;

	std::vector<Mesh*> meshes;

	std::vector<std::vector<Mesh*>> tileSets;

	void Initialize();
	void LoadTileSet(const std::string& name, int start, int end);

public:
	ObjectBuilder();
	ObjectBuilder(Camera* camera);
	~ObjectBuilder();

	Object* CreateObject(ObjectType type);
	Object* CreateObject(ObjectType type, vec2 scale, vec2 pos, float o);
	Object* CreateTile(TileSetType type, int num, vec2 scale, vec2 pos, float o);
	
	void UpdateShaders(float t);
};
