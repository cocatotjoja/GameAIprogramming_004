#pragma once
#include <stack>

#include "raylib.h"

#include "globals.h"
#include "map.h"



class Worker
{
public:
	Map* map;
	States state = SCOUT;
	Vector2 position;
	Vector2 velocity = { 0, 0 };
	float maxAcceleration = 400;
	float maxSpeed = 2.0f;
	stack<Vector2> path;
	bool followingPath = false;
	bool harvesting = false;

	Product product;
	int materialID;
	WorkshopType workshop;
	float timer = 0;
	int wood = 0;
	int ore = 0;
	int coal = 0;
	int bar = 0;
	int sword = 0;


	Worker() : position({ 0, 0 }) {};
	Worker(Vector2 pos, Map* newMap) : position(pos), map(newMap) {};
	virtual void Update();
	void Draw();

	Vector2 Seek(Vector2 targetPos);
	void FollowPath();
	bool HaveProduct();
	
	bool IsFree();
	void GetProduct(Product newProduct, WorkshopType newWorkshopType);
	void Harvest();
	void Transport();
	void Search();
};

class Scout : public Worker
{
private:
	Vector2 target = { (float)-1, (float)-1 };

public:
	Scout() {};
	Scout(Vector2 newPos, Map* newMap);

	void Update();
	void Draw();
	void Scouting();
};

class Soldier : public Worker
{
private:

public:
	Soldier() {};
	Soldier(Vector2 newPos, Map* newMap) : Worker(newPos, newMap) {};
	Soldier(float time, Vector2 newPos, Map* newMap);

	void Update();
	void Draw();
};

class Crafter : public Worker
{
	CrafterType type;
	float craftingTime;

public:
	Crafter() : type(BUILDER) {};
	Crafter(CrafterType newType, Vector2 newPos, Map* newMap) : Worker(newPos, newMap), type(newType) {};

	void GetCrafting();
	void Update();
	void Draw();

	CrafterType GetType() { return type; };
	void Crafting();
};
