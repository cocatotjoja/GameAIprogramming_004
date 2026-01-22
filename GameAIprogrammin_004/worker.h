#pragma once
#include <vector>
#include "raylib.h"
#include "raymath.h"

#include "globals.h"
#include "map.h"

class Worker
{
public:
	Vector2 position;
	States currentState = IDLE;

	Worker() : position({ 0, 0 }) {};
	Worker(int x, int y) : position(Vector2{ (float)x, (float)y }) {};
	void Update(Map map);
	void Draw();
	
};
