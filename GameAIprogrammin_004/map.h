#pragma once
#include <vector>
#include <stack>
#include "raylib.h"
#include "raymath.h"

#include "objects.h"
#include "globals.h"
#include "mapReader.h"
#include "Pathfinder.h"

using namespace std;

class Map
{
	MapReader rm;
	Pathfinder pathfinder;
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
	Vector2 GetFogPos(Vector2 quad);
	Vector2 GetFogPosRand();
	void RemoveFog(Vector2 index);
	void GetPath(Vector2 start, Vector2 goal, std::stack<Vector2>& returnPath);
};
