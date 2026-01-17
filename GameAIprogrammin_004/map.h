#pragma once
#include <vector>
#include "raylib.h"
#include "raymath.h"

#include "squares.h"
#include "objects.h"
#include "globals.h"
#include "mapReader.h"

using namespace std;

class Map
{
	MapReader rm;
	vector<Tree> trees;
	vector<Ore> ironOre;
	vector<Terrain> land;
	vector<Rectangle> swamps;
	
public:
	Map();
	void Draw();
	void MakeMap();
	//void AddTree(Vector2 pos);
	void AddOre();

	bool IsBlocked(int x, int y);
};
