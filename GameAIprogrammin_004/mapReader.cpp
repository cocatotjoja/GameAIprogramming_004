#include "mapReader.h"

MapReader::MapReader()
{
	for (int i = 0; i < 10000; i++)
	{
		int x = i % 100;
		int y = i / 100;

		mapGrid[x][y] = charMap[i];
	}
}