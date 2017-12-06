#include "Scene.h"
#include <iostream>
#include <time.h>

using namespace std;

Scene::Scene(){
	width = 100;
	height = 100;
	scale = .5;

	Initialize();
}

Scene::~Scene() {

	for (map<string, Object*>::iterator it = objectMap.begin();
		it != objectMap.end(); it++) {
		delete it->second;
	}
	for (map<string, Object*>::iterator it = tileMap.begin();
		it != tileMap.end(); it++) {
		delete it->second;
	}
	if (objectBuilder) delete objectBuilder;
	if (camera) delete camera;
	if (avatarLight) delete avatarLight;
}

void Scene::Initialize() {
	camera = new Camera();
	objectBuilder = new ObjectBuilder(camera);
	avatarLight = new Light(vec2(0, 0));

	Create(BACKGROUND, vec2(3.55, 2), "BACKGROUND", false);
	camera->BindBackground(objectMap["BACKGROUND"]);
	GenerateWorld();
	Create(ROBOT, vec2(.5, .5), "AVATAR", false);
}

void Scene::GenerateWorld() {
	worldMatrix = new int*[height];
	for (int i = 0; i < height; i++) {
		worldMatrix[i] = new int[width];
		for (int j = 0; j < width; j++) {
			worldMatrix[i][j] = 0;
		}
	}

	for (int i = 0; i < height; i++) {
		worldMatrix[i][0] = 1;
		worldMatrix[i][width-1] = 1;
	}

	for (int i = 0; i < width; i++) {
		worldMatrix[0][i] = 1;
		worldMatrix[height - 1][i] = 1;
	}

	srand(time(NULL));

	int islandRand = (width * height) / 500 + 1;
	int islandGuarentee = (width * height) * .002;
	int numIslands = islandGuarentee + rand() % islandRand;
	cout << numIslands << " " << islandGuarentee << " " << islandRand << endl;

	
	for (int i = 0; i < numIslands; i++) {
		int iRand = rand() % (height-2);
		int jRand = rand() % (width-2);
		worldMatrix[iRand][jRand] = 1;
	}

	int genRounds = 20;
	int valNeeded = 10;
	for (int i = 0; i < genRounds; i++) {
		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {
				int val = worldMatrix[i - 1][j] + worldMatrix[i + 1][j]
					+ worldMatrix[i][j - 1] * 2 + worldMatrix[i][j + 1] * 2;
				int generated = rand() % valNeeded;
				if (generated < val) {
					worldMatrix[i][j] = 1;
				}
			}
		}
	}

	int centerRow = (height-1) / 2 + 1/scale;
	int centerCol = (width-1) / 2 + 1;
	for (int i = centerRow - 1 / scale; i < centerRow + 1 + 1 / scale; i++) {
		for (int j = centerCol - 1 / scale; j < centerCol + 1 + 1 / scale; j++) {
			worldMatrix[i][j] = 0;
			if (i == centerRow - 1 / scale) {
				worldMatrix[i][j] = 1;
			}
		}
	}

	float offSetX = -1 * scale * width / 2.0;
	float offSetY = -1 * scale * width / 2.0;
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (worldMatrix[i][j] == 1) {
				float x = offSetX + j * scale;
				float y = offSetY + i * scale;
				ostringstream os;
				os << "tile " << i << " " << j;

				if (i > 0 && i < height - 1
					&& j > 0 && j < width - 1) {

					int val = 1;
					if (worldMatrix[i + 1][j] == 1) {
						//something above
						val = 4;
						val = val - worldMatrix[i][j + 1] + worldMatrix[i][j - 1];
					}
					else {
						//not something
						val = val - worldMatrix[i][j + 1] + worldMatrix[i][j - 1];
						if (worldMatrix[i][j + 1] == 0 && worldMatrix[i][j - 1] == 0) {
							val = 4;
						}
					}
					CreateTile(TIL_MACHINE, val, vec2(scale, scale), vec2(x, y), os.str());
				} else 
					CreateTile(TIL_MACHINE, 4, vec2(scale, scale), vec2(x, y), os.str());
			}
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << worldMatrix[i][j] << "";
		}
		cout << endl;
	}
}

void Scene::Create(ObjectType type, std::string id, bool collide) {
	objectMap[id] = (objectBuilder->CreateObject(type));
	/*
	if (collide) {
		tiles.push_back(objects.back());
		tileIds.push_back(id);
	}*/
}

void Scene::Create(ObjectType type, vec2 scale, std::string id, bool collide) {
	objectMap[id] = (objectBuilder->CreateObject(type, scale, vec2(0, 0), 0));
	/*
	if (collide) {
		tiles.push_back(objects.back());
		tileIds.push_back(id);
	}*/
}

void Scene::Create(ObjectType type, vec2 scale, vec2 position, std::string id, bool collide) {
	objectMap[id] = (objectBuilder->CreateObject(type, scale, position, 0));
	/*
	if (collide) {
		tiles.push_back(objects.back());
		tileIds.push_back(id);
	}*/
}

void Scene::Create(ObjectType type, vec2 scale, vec2 position, float orientation, std::string id, bool collide) {
	objectMap[id] = (objectBuilder->CreateObject(type, scale, position, orientation));
	/*
	if (collide) {
		tiles.push_back(objects.back());
		tileIds.push_back(id);
	}*/
}

void Scene::CreateTile(TileSetType type, int num, std::string id) {
	tileMap[id] = objectBuilder->CreateTile(type, num, vec2(1, 1), vec2(0, 0), 0);
}

void Scene::CreateTile(TileSetType type, int num, vec2 scale, std::string id) {
	tileMap[id] = objectBuilder->CreateTile(type, num, scale, vec2(0, 0), 0);
}

void Scene::CreateTile(TileSetType type, int num, vec2 scale, vec2 position, std::string id) {
	tileMap[id] = objectBuilder->CreateTile(type, num, scale, position, 0);
}

void Scene::CreateTile(TileSetType type, int num, vec2 scale, vec2 position, float orientation, std::string id) {
	tileMap[id] = objectBuilder->CreateTile(type, num, scale, position, orientation);
}

void Scene::RemoveObject(std::string id) {
	objectMap.erase(id);
}
void Scene::RemoveTile(std::string id) {
	tileMap.erase(id);
}

vector<Object*> Scene::GetScreenTiles() {
	vector<Object*> screenTiles;
	vec2 camPosition = camera->GetPosition();
	float offSetX = -1 * scale * width / 2.0;
	float offSetY = -1 * scale * width / 2.0;
	int realX = camPosition.x - offSetX;
	int realY = camPosition.y - offSetY;
	int iCenter = realY / scale;
	int jCenter = realX / scale;
	for (int i = iCenter - 2 / scale; i < iCenter + 2 / scale; i++) {
		for (int j = jCenter - 2 / scale; j < jCenter + 3 / scale; j++) {
			ostringstream os;
			os << "tile " << i << " " << j;
			if (tileMap[os.str()]) {
				screenTiles.push_back(tileMap[os.str()]);
			}
		}
	}
	return screenTiles;
}

vector<Object*> Scene::GetAdjacentTiles(Object* object) {
	vector<Object*> adjacentTiles;
	vec2 pos = object->GetPosition();
	float offSetX = -1 * scale * width / 2.0;
	float offSetY = -1 * scale * width / 2.0;
	int realX = pos.x - offSetX;
	int realY = pos.y - offSetY;
	int iCenter = realY / scale;
	int jCenter = realX / scale;
	for (int i = iCenter - 1; i < iCenter + 3; i++) {
		for (int j = jCenter - 1; j < jCenter + 3; j++) {
			ostringstream os;
			os << "tile " << i << " " << j;
			if (tileMap[os.str()]) {
				adjacentTiles.push_back(tileMap[os.str()]);
			}
		}
	}
	return adjacentTiles;
}

void Scene::Draw() {
	Object* avatar = objectMap["AVATAR"];
	if (avatar) {
		vec2 avatarPosition = avatar->GetPosition();
		camera->SetPosition(vec2(avatarPosition.x - CENTER.x, avatarPosition.y - CENTER.y));
	}

	objectBuilder->UpdateShaders(lastT);

	if (objectMap["BACKGROUND"]) {
		objectMap["BACKGROUND"]->Draw();
	}

	vector<Object*> screenTiles = GetScreenTiles();
	for (Object* o : screenTiles) {
		o->Draw();
	}

	for (map<string, Object*>::iterator it = objectMap.begin();
		it != objectMap.end(); it++) {
		if (it->first != "AVATAR" && it->first != "BACKGROUND") {
			it->second->Draw();
		}
	}
	if (objectMap["AVATAR"]) {
		objectMap["AVATAR"]->Draw();
	}
}

bool Scene::OnScreen(Object* obj) {
	vec2 camPos = camera->GetPosition();
	vec2 objPos = obj->GetPosition();
	if (objPos.x > camPos.x - 1 && objPos.x < camPos.x + 1
		&& objPos.y > camPos.y - 1 && objPos.y < camPos.y + 1) {
		return true;
	}
	return false;
}

void Scene::Update(float t, bool keyStates[256]) {
	Object* avatar = objectMap["AVATAR"];
	if (avatar) {
		vec2 pos = avatar->GetPosition();

		vec2 velocity = avatar->GetVelocity();
		if (keyStates['d']) velocity.x = 1;
		else if (keyStates['a']) velocity.x = -1;
		else velocity.x = 0;

		avatar->SetVelocity(velocity);

		if (keyStates[' ']) avatar->Jump();
	}

	float dt = t - lastT;

	//max out the dt
	if (dt > .05) {
		dt = .05;
	}

	vector<Object*> screenTiles = GetScreenTiles();
	for (map<string, Object*>::iterator it = objectMap.begin();
		it != objectMap.end(); it++) {
		it->second->ApplyGravity(dt);
		it->second->Animate(t);
		if (it->second->Moveable()) {
			vector<Object*> adjacentTiles = GetAdjacentTiles(it->second);
			it->second->Move(dt, adjacentTiles);
		}
	}

	if (avatar) avatarLight->SetPosition(objectMap["AVATAR"]->GetPosition());

	lastT = t;
}

void Scene::Resize(int width, int height) {
	camera->SetAspectRatio(height, width);
}