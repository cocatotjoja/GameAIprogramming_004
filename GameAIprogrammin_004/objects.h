#pragma once
#include "raylib.h"
#include "raymath.h"
#include "globals.h"



class Tree
{
	Vector2 position = { 0, 0 };
public:
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

class Workshop
{
	float timer;
	WorkshopType type;
	WorkshopState state;
	Vector2 position;

	int wood = 0;
	int ore = 0;
	int coal = 0;
	int bar = 0;
	int sword = 0;

public:
	Workshop(WorkshopType newType, float newTime, Vector2 pos, WorkshopState newState) : timer(newTime), type(newType), position(pos), state(newState) {};
	~Workshop() {};
	void AddMaterial(Product product);
	void RemoveMaterial(Product product);
	int CheckInventory(Product product);
	WorkshopState GetState() { return state; };
};