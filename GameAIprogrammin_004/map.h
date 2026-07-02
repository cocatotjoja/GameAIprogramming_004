#pragma once
#include <vector>
#include <stack>
#include "raylib.h"
#include "raymath.h"

#include "objects.h"
#include "globals.h"
#include "mapReader.h"

using namespace std;

class Map
{
	MapReader rm;
	vector<Tree> trees;
	vector<Ore> ironOre;
	vector<Rectangle> swamps;
	vector<Workshop> workshops;
	
public:
	Map();
	void Draw();
	void MakeMap();
	void AddTree(Vector2 pos);
	void AddOre();

	Workshop* GetWorkshop(WorkshopType type);
};
