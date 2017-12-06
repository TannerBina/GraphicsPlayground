#pragma once
#include <string>
#include "Util.h"
#include <sstream>
#include <iostream>

extern "C" unsigned char* stbi_load(char const * filename,
	int * x, int * y, int* comp, int req_comp);

class Texture {
	unsigned int textureId;
	int numRows;
	int numCols;
	float animationTime;

public:
	Texture(const std::string & inputFileName);
	Texture(const std::string & inputFileName, int numRows, 
		int numCols, float animationTime);

	void Bind();

	int GetNumRows() { return numRows; }
	int GetNumCols() { return numCols; }
	float GetAnimationTime(){ return animationTime; }

	static std::vector<Texture*> BuildTileSet(const std::string & folderName, int startNum, int endNum) {
		std::vector<Texture*> res;
		for (int i = startNum; i < endNum + 1; i++) {
			std::ostringstream os;
			os << folderName << "/" << "Tile (" << i << ").png";
			res.push_back(new Texture(os.str()));
		}
		return res;
	}
};

