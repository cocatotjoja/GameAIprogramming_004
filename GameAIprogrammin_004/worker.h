#pragma once
#include <stack>

#include "raylib.h"
#include "raymath.h"

#include "globals.h"
#include "map.h"

class Worker
{
public:
	States state = IDLE;
	Vector2 position;
	Vector2 velocity = { 0, 0 };
	float maxAcceleration = 400;
	float maxSpeed = 2.0f;
	stack<Vector2> path;
	bool followingPath = false;
	bool harvesting = false;
	bool transforming = false;
	Product product;
	WorkshopType workshop;
	int timer = 0;
	int wood = 0;
	int ore = 0;
	int coal = 0;
	int bar = 0;
	int sword = 0;


	Worker() : position({ 0, 0 }) {};
	Worker(Vector2 pos) : position(pos) {};
	virtual void Update();
	void Draw();

	Vector2 Seek(Vector2 targetPos);
	void FollowPath();
	bool HaveProduct();
	
	bool IsFree();
	void GetProduct(Product newProduct, WorkshopType newWorkshopType);
	void Harvest();
	void Transport();
};

class Scout : public Worker
{
private:
	Vector2 target = { (float)-1, (float)-1 };

public:
	Scout() {};
	Scout(Vector2 newPos) : Worker(newPos) {};

	void Update();
	void Scouting();
};

class Soldier : public Worker
{
private:

public:
	Soldier() {};
	Soldier(Vector2 newPos) : Worker(newPos) {};

	void Update();
};

class Crafter : public Worker
{
	CrafterType type;

public:
	Crafter() : type(BUILDER) {};
	Crafter(CrafterType newType, Vector2 newPos) : Worker(newPos), type(newType) {};

	void GetCrafting(int time);
	void Update();

	CrafterType GetType() { return type; };
	void Crafting();
};
