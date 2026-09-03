#include "map.h"
#include "StaffManager.h"


Map::Map()
{
	MakeMap();
}

void Map::Draw()
{
	// Draw land
	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			rm.mapGrid[x][y].Draw();
		}
	}

	// Draw objects
	for (Tree t : trees)
	{
		t.Draw();
	}
	for (Ore o : ironOre)
	{
		o.Draw();
	}



	// Draw Fog
	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			rm.mapGrid[x][y].DrawFog();
		}
	}
}

void Map::MakeMap()
{
	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			char def = rm.mapGrid[x][y].GetType();
			Vector2 pos = { (float)x * 10, (float)y * 10 };

			//Change color based on terrain type
			if (def == 'T')
			{
				// Add three trees
				AddTree(pos);
				AddTree(pos);
				AddTree(pos);
				AddTree(pos);
				AddTree(pos);
			}
			else if (def == 'G')
			{
				// Add boundingbox for lower speed
				Rectangle boundary = { pos.x * resMult, pos.y * resMult, 10 * resMult, 10 * resMult };
				swamps.push_back(boundary);
			}
		}
	}

	// Add 60 iron ore
	AddOre();

	Vector2 temPos = { 0, 0 };
	AddWorkshop(COAL_MILL, temPos);
	AddWorkshop(SMELT, temPos);
	AddWorkshop(FORGE, temPos);
	AddWorkshop(TRAINING_CAMP, temPos);

	// Remove fog from 9x9
	for (size_t x = 21; x < 30; x++)
	{
		for (size_t y = 36; y < 45; y++)
		{
			rm.mapGrid[x][y].RemoveFog();
		}
	}
}

void Map::AddTree(Vector2 pos)
{
	int x = RandomIntRange(1, 9);
	int y = RandomIntRange(1, 9);

	pos += Vector2{ (float)x, (float)y };

	trees.push_back(pos);
}

void Map::AddOre()
{
	for (int i = 0; i < 60; i++)
	{
		int x = RandomIntRange(0,99);
		int y = RandomIntRange(0,99);
		// Check not blocked or used
		while (rm.mapGrid[x][y].IsBlocked())
		{
			x = RandomIntRange(0,99);
			y = RandomIntRange(0,99);
		}
		int Px = RandomIntRange(2, 8);
		int Py = RandomIntRange(2, 8);
		ironOre.push_back(Vector2{ (float)x*10+Px, (float)y*10+Py });
	}
}

void Map::AddWorkshop(WorkshopType type, Vector2 position)
{
	switch (type)
	{
	case COAL_MILL:
		workshops.push_back(Workshop(type, 60.0f, position, AVAILABLE, COAL, this, staff));				// Float is the one needed for building the workshop
		break;
	case SMELT:
		workshops.push_back(Workshop(type, 120.0f, position, AVAILABLE, BAR, this, staff));				// Float is the one needed for building the workshop
		break;
	case FORGE:
		workshops.push_back(Workshop(type, 180.0f, position, AVAILABLE, SWORD, this, staff));			// Float is the one needed for building the workshop
		break;
	case TRAINING_CAMP:
		workshops.push_back(Workshop(type, 120.0f, position, AVAILABLE, SOLDIER, this, staff));			// Float is the one needed for building the workshop
		break;
	default:
		break;
	}
}

Workshop* Map::GetWorkshop(WorkshopType type)
{
	switch (type)
	{
	case COAL_MILL:
		return &workshops[0];
	case SMELT:
		return &workshops[1];
	case FORGE:
		return &workshops[2];
	case TRAINING_CAMP:
		return &workshops[3];
	default:
		return nullptr;
	}
}

bool Map::HaveWorkshop(WorkshopType type)
{
	for (Workshop ws : workshops)
	{
		if (ws.GetType() == type && ws.IsBuilt())
		{
			true;
		}
	}
	return false;
}

Vector2 Map::GetFogPosRand()
{
	if (IsFoggy())
	{
		int x = RandomIntRange(0, 99);
		int y = RandomIntRange(0, 99);
		// Check not blocked or used
		while (rm.mapGrid[x][y].IsBlocked() || rm.mapGrid[x][y].IsFogged() == false)
		{
			x = RandomIntRange(1, 98);
			y = RandomIntRange(1, 98);
		}
		return Vector2{ (float)x, (float)y };
	}

	return Vector2{ -1, -1 };
}

void Map::RemoveFog(Vector2 index)
{
	int x = index.x;
	int y = index.y;
	rm.mapGrid[x][y].RemoveFog();
}

bool Map::IsFoggy()
{
	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			if (rm.mapGrid[x][y].IsFogged() && rm.mapGrid[x][y].IsBlocked() == false)
			{
				return true;
			}
		}
	}
	return false;
}

void Map::GetPath(Vector2 start, Vector2 goal, std::stack<Vector2>& returnPath)
{
	pathfinder.FindPath(rm.mapGrid, start, goal, returnPath);
}

int Map::GetTree()
{
	for (size_t i = 0; i < trees.size(); i++)
	{
		if (trees[i].booked == false)
		{
			Vector2 treeNode = GetNearestNode(trees[i].position);
			if (rm.mapGrid[(int)treeNode.x][(int)treeNode.y].IsBlocked() == false && rm.mapGrid[(int)treeNode.x][(int)treeNode.y].IsFogged() == false)
			{
				return i;
			}
		}
	}
	return -1;
}

int Map::GetOre()
{
	for (size_t i = 0; i < ironOre.size(); i++)
	{
		if (ironOre[i].booked == false)
		{
			Vector2 treeNode = GetNearestNode(ironOre[i].position);
			if (rm.mapGrid[(int)treeNode.x][(int)treeNode.y].IsBlocked() == false && rm.mapGrid[(int)treeNode.x][(int)treeNode.y].IsFogged() == false)
			{
				return i;
			}
		}
	}
	return -1;
}

