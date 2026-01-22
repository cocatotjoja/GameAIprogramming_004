#include "map.h"

Map::Map()
{
	MakeMap();
}

void Map::Draw()
{
	for (Terrain l : land)
	{
		l.Draw();
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
			char def = rm.mapGrid[x][y];
			Vector2 pos = { x * 10, y * 10 };
			Color type = Mgreen;

			//Change color based on terrain type
			if (def == 'T')
			{
				// Add three trees
				//AddTree(pos);
				//AddTree(pos);
				//AddTree(pos);
				type = MdarkGreen;
			}
			else if (def == 'V')
			{
				// Add space to unwalkables
				type = Mblue;
			}
			else if (def == 'G')
			{
				// Add boundingbox for lower speed
				type = MdarkBrown;
				Rectangle boundary = { pos.x * resMult, pos.y * resMult, 10 * resMult, 10 * resMult };
				swamps.push_back(boundary);
			}
			else if (def == 'B')
			{
				// Add space to unwalkables
				type = Mburgundy;
			}

			land.push_back(Terrain(pos, Vector2{10, 10}, type));
		}
	}

	// Add 60 iron ore
	AddOre();
}

void Map::AddOre()
{
	for (int i = 0; i < 60; i++)
	{
		int x = RandomIntRange(0,100);
		int y = RandomIntRange(0,100);
		// Check not blocked or used
		while (IsBlocked(x, y))
		{
			x = RandomIntRange(0,100);
			y = RandomIntRange(0,100);
		}
		x += RandomIntRange(0, 9);
		y += RandomIntRange(0, 9);
		ironOre.push_back(Vector2{ (float)x*10, (float)y*10 });
	}
}

bool Map::IsBlocked(int x, int y)
{
	if (rm.mapGrid[x][y] == 'B' || rm.mapGrid[x][y] == 'V')
	{
		return true;
	}
	return false;
}
