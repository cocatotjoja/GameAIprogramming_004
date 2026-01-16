#pragma once
#include "raylib.h"
#include "raymath.h"
#include "colors.h"



class Tree
{
	Vector2 position = { 0, 0 };
	Vector2 size = { 1, 1 };
public:
	bool grown = true;
	Tree() {};
	Tree(Vector2 pos) : position(pos) {};
};



class Ore
{
	Vector2 position = { 0, 0 };
	Vector2 size = { 1, 1 };
public:
	Ore() {};
	Ore(Vector2 pos) : position(pos) {};
};
