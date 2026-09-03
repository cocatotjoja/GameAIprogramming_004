#pragma once
#include "raylib.h"
#include "raymath.h"

#include "globals.h"
//#include "map.h"
//#include "StaffManager.h"

class Map;
class StaffManager;



class Tree
{

public:
	Vector2 position = { 0, 0 };
	bool booked = false;
	bool cut = false;

	Tree() {};
	Tree(Vector2 pos) : position(pos* resMult) {};
	void Draw();
};



class Ore
{
public:
	Vector2 position = { 0, 0 };
	bool booked = false;
	bool cut = false;

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
	Product produce;
	bool built = false;
	int orders = 0;

	Map* map;
	StaffManager* staff;

	int wood = 0;
	int ore = 0;
	int coal = 0;
	int bar = 0;
	int sword = 0;

public:
	Workshop(WorkshopType newType, float newTime, Vector2 pos, WorkshopState newState, Product productType, Map* newMap, StaffManager* newStaff) : timer(newTime), type(newType), position(pos), state(newState), produce(productType), map(newMap), staff(newStaff) {};
	~Workshop() {};
	void Update();
	void Draw();

	void AddMaterial(Product product);
	void RemoveMaterial(Product product);
	int CheckInventory(Product product);
	int CheckOrders() { return orders; };
	void PlaceOrder(int amount) { orders += amount; };
	WorkshopType GetType() { return type; };
	WorkshopState GetState() { return state; };
	void SetState(WorkshopState newState) { state = newState; };
	bool IsBuilt() { return built; };
	Vector2 GetPosition() { return position; };

	void Running();
	void Waiting();
};