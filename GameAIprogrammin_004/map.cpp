#include "map.h"

Map::Map()
{
	MakeMap();
}

void Map::Draw()
{
	
	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			rm.mapGrid[x][y].Draw();
		}
	}

	for (Tree t : trees)
	{
		t.Draw();
	}
	for (Ore o : ironOre)
	{
		o.Draw();
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

	workshops.push_back(Workshop(COAL_MILL, 60.0f, Vector2{ 0.0f, 0.0f }, NOT_BUILT));						// Time is the one needed for building the workshop
	workshops.push_back(Workshop(SMELT, 120.0f, Vector2{ 0.0f, 0.0f }, NOT_BUILT));
	workshops.push_back(Workshop(FORGE, 180.0f, Vector2{ 0.0f, 0.0f }, NOT_BUILT));
	workshops.push_back(Workshop(TRAINING_CAMP, 120.0f, Vector2{ 0.0f, 0.0f }, NOT_BUILT));

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

Vector2 Map::GetFogPos(Vector2 quad)
{
	for (size_t x = quad.x; x < 100; x++)
	{
		for (size_t y = quad.y; y < 100; y++)
		{
			if (rm.mapGrid[x][y].IsFogged() && rm.mapGrid[x][y].IsBlocked() == false)
			{
				return Vector2{ (float)x, (float)y };
			}
		}
	}
	return Vector2{ -1, -1 };
}

Vector2 Map::GetFogPosRand()
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

void Map::RemoveFog(Vector2 index)
{
	int x = index.x;
	int y = index.y;
	rm.mapGrid[x][y].RemoveFog();
}

void Map::GetPath(Vector2 start, Vector2 goal, std::stack<Vector2>& returnPath)
{
	pathfinder.FindPath(rm.mapGrid, start, goal, returnPath);
}

