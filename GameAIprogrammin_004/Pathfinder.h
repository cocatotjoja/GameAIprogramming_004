#pragma once
#include "node.h"
#include <stack>



class Pathfinder
{
private:
	std::vector<Node*> opened;
	std::vector<Node*> closed;

	bool found = false;
	bool addStart = true;

	Pathfinder() {};
	~Pathfinder() {};
	int ShouldAdd(Node (&map1)[100][100], int x, int y, int corner, int width, int height);
	void AddNode(Node (&map1)[100][100], Vector2 parentID, int parentXplus, int parentYplus, float addValue, int corner, float parentValue, int width, int height, Vector2 goal);

public:
	void FindPath(Node (&map1)[100][100], int width, int height, Vector2 start, Vector2 goal, std::stack<Vector2> &returnPath);

};