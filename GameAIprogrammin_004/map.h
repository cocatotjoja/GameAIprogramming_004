#pragma once
#include <vector>
#include "raylib.h"
#include "raymath.h"

#include "squares.h"
#include "objects.h"

using namespace std;

class Map
{
	vector<Tree> trees;
	vector<Ore> ironOre;
	vector<Terrain> land;
	Map();

	void MakeMap(char mapGrid[100][100]);
	void AddLand(Vector2 pos);
	void AddTree(Vector2 pos);
	void AddOre();
};
