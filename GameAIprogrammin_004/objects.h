#pragma once
#include "raylib.h"
#include "raymath.h"
#include "globals.h"



class Tree
{
	Vector2 position = { 0, 0 };
public:
	bool grown = true;
	Tree() {};
	Tree(Vector2 pos) : position(pos* resMult) {};
	void Draw();
};



class Ore
{
	Vector2 position = { 0, 0 };
public:
	Ore() {};
	Ore(Vector2 pos) : position(pos* resMult) {};
	void Draw();
};
