#include"ObjectBuilder.h"
#include "StateObject.h"
#include "CollideableObject.h"

ObjectBuilder::ObjectBuilder() {
	camera = new Camera();

	Initialize();
}

ObjectBuilder::ObjectBuilder(Camera* camera) {
	this->camera = camera;

	Initialize();
}

ObjectBuilder::~ObjectBuilder() {
	for (Shader* s : shaders) delete s;
	for (Texture* t : textures) delete t;
	for (Material* m : materials) delete m;
	for (Geometry* g : geometries) delete g;
	for (Mesh* m : meshes) delete m;

	for (std::vector<Mesh*> v : tileSets) {
		for (Mesh* m : v) {
			delete m->GetGeometry();
			delete m->GetTexture();
			delete m->GetMaterial();
			delete m;
		}
	}

	if (camera) delete camera;
}

void ObjectBuilder::Initialize() {
	shaders.push_back(new TextureShader());
	shaders.push_back(new ColorShader());

	textures.push_back(new Texture("spritesheetRunningGirl.png"));
	textures.push_back(new Texture("robot.png"));
	textures.push_back(new Texture("game_background.png"));

	LoadTileSet("Machine", 1, 6);

	materials.push_back(new Material(shaders[SHA_TEXTURE],
		vec4(1, 1, 1, 1),
		textures[TEX_RUNNING_GIRL]));
	materials.push_back(new Material(shaders[SHA_TEXTURE],
		vec4(1, 1, 1, 1),
		textures[TEX_ROBOT]));
	materials.push_back(new Material(shaders[SHA_COLOR],
		vec4(1, 0, 0, 1)));
	materials.push_back(new Material(shaders[SHA_TEXTURE],
		vec4(1, 1, 1, 1),
		textures[TEX_BACKGROUND]));

	geometries.push_back(new TexturedQuad());
	geometries.push_back(new SpriteSheetQuad("robot.txt"));
	geometries.push_back(new Quad());

	meshes.push_back(new Mesh(materials[MAT_RUNNING_GIRL],
		geometries[GEO_TEXTURED_QUAD]));
	meshes.push_back(new Mesh(materials[MAT_ROBOT],
		geometries[GEO_SS_QUAD]));
	meshes.push_back(new Mesh(materials[MAT_RED],
		geometries[GEO_QUAD]));
	meshes.push_back(new Mesh(materials[MAT_BACKGROUND],
		geometries[GEO_TEXTURED_QUAD]));
}

void ObjectBuilder::LoadTileSet(const std::string& name, int start, int end) {
	std::vector<Texture*> texs = Texture::BuildTileSet(name, start, end);
	std::vector<Material*> mats;
	for (Texture* t : texs) {
		mats.push_back(new Material(shaders[SHA_TEXTURE],
			vec4(1, 1, 1, 1), t));
	}
	std::vector<Mesh*> mesh;
	for (Material* m : mats) {
		mesh.push_back(new Mesh(m, new TexturedQuad()));
	}
	
	tileSets.push_back(mesh);
}

Object* ObjectBuilder::CreateObject(ObjectType type) {
	vec2 scale(1, 1);
	vec2 pos(0, 0);
	float o = 0;

	return CreateObject(type, scale, pos, o);
}

Object* ObjectBuilder::CreateTile(TileSetType type, int num, vec2 scale, vec2 pos, float o) {
	return new CollideableObject(camera, tileSets[type][num], pos, scale, o, TILE);
}

Object* ObjectBuilder::CreateObject(ObjectType type, vec2 scale, vec2 pos, float o) {	
	switch (type) {
	case RUNNING_GIRL:
		return new Object(camera, meshes[type], pos, scale, o, type);
		break;
		
	case ROBOT:
		return new StateObject(camera, meshes[type], pos, scale, o, type);
		break;

	case RED_BLOCKING_SQUARE:
		return new CollideableObject(camera, meshes[type], pos, scale, o, type);
		break;

	case BACKGROUND:
		return new Object(camera, meshes[type], pos, scale, o, type);
		break;
	default:
		return new Object(camera, meshes[type], pos, scale, o, type);
		break;
	}
}

void ObjectBuilder::UpdateShaders(float t) {
	for (Shader* s : shaders) s->UploadTime(t);
}