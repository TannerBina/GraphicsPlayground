#pragma once

#include "ObjectBuilder.h"
#include <string>
#include <map>
#include "Light.h"

class Scene {
	Light* avatarLight;

	int width;
	int height;
	float scale;
	int** worldMatrix;

	float lastT;
	Camera* camera;
	ObjectBuilder* objectBuilder;
	std::map<std::string, Object*> objectMap;
	std::map<std::string, Object*> tileMap;

	void Initialize();

	void GenerateWorld();

	void Create(ObjectType type, std::string id, bool collide);
	void Create(ObjectType type, vec2 scale, std::string id, bool collide);
	void Create(ObjectType type, vec2 scale, vec2 position, std::string id, bool collide);
	void Create(ObjectType type, vec2 scale, vec2 position, float orientation, std::string id, bool collide);

	void CreateTile(TileSetType type, int num, std::string id);
	void CreateTile(TileSetType type, int num, vec2 scale, std::string id);
	void CreateTile(TileSetType type, int num, vec2 scale, vec2 position, std::string id);
	void CreateTile(TileSetType type, int num, vec2 scale, vec2 position, float orientation, std::string id);

	void RemoveObject(std::string id);
	void RemoveTile(std::string id);

	//TODO ADJUST BOTH METHODS FOR HX and HY
	std::vector<Object*> GetScreenTiles();
	std::vector<Object*> GetAdjacentTiles(Object* object);
	bool OnScreen(Object* obj);

public:
	Scene();
	~Scene();

	void Draw();
	void Update(float t, bool keyStates[256]);
	void Resize(int width, int height);
};
