#include "map.h"

void Map::MakeMap(char mapGrid[100][100])
{
	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			char def = mapGrid[x][y];
			Color type = green;

			//Change color based on terrain type

			Vector2 pos = { x * 10, y * 10 };
			land.push_back(Terrain(pos, Vector2{10,10}, type));

			// If terrain is Swamp add a bounding box for lowering speed
			// If terrain is Woods add three trees
		}
	}
}
