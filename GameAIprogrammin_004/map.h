#pragma once
#include <vector>
#include <stack>
#include "raylib.h"
#include "raymath.h"

#include "objects.h"
#include "globals.h"
#include "mapReader.h"
#include "Pathfinder.h"
//#include "StaffManager.h"

class StaffManager;

using namespace std;

class Map
{
	StaffManager* staff;
	MapReader rm;
	Pathfinder pathfinder;
	
public:
	vector<Tree> trees;
	vector<Ore> ironOre;
	vector<Rectangle> swamps;
	vector<Workshop> workshops;

	Map();
	Map(StaffManager* newStaff) : staff(newStaff) {};
	void Draw();
	void MakeMap();
	void AddTree(Vector2 pos);
	void AddOre();
	void AddWorkshop(WorkshopType type, Vector2 position);

	Workshop* GetWorkshop(WorkshopType type);
	bool HaveWorkshop(WorkshopType type);
	Vector2 GetFogPosRand();
	void RemoveFog(Vector2 index);
	bool IsFoggy();
	void GetPath(Vector2 start, Vector2 goal, std::stack<Vector2>& returnPath);
	int GetTree();
	int GetOre();
};
