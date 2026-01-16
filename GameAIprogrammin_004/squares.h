#pragma once
#include "raylib.h"
#include "raymath.h"
#include "colors.h"

class Terrain
{
	Vector2 position = { 0, 0 };
	Vector2 size = { 10, 10 };
	Rectangle boundary = { position.x, position.y, size.x, size.y };
	Color ground = green;

public:
	Terrain(){};
	Terrain(Vector2 pos, Vector2 sides, Color type) : position(pos), size(sides), ground(type) {};
	virtual void Draw();
};
