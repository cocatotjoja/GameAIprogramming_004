#pragma once
#include "raylib.h"
#include "raymath.h"
#include "globals.h"

class Node
{
private:
	Vector2 ID;
	Vector2 position;
	char type;
	Vector2 size = { 10.0f * resMult, 10.0f * resMult };
	Color ground = Mgreen;


	// Pathfinder variables
	float valueSofar = NULL;
	float valueLeft = NULL;
	float valueTotal = NULL;
	Vector2 parent;

	// Unchecked = 1, Opened = 2, Closed = 3, Path = 4
	int state = 1;
	bool blocked = false;
	bool fog = true;

public:
	Node();
	Node(int x, int y, char Type);

	char GetType() { return type; };
	void SetType(char newType) { type = newType; };
	Vector2 GetPosition() { return position; };
	Vector2 GetID() { return ID; };
	bool IsBlocked();
	int GetState() { return state; };
	void SetState(int newState) { state = newState; };
	void SetBlocked(bool block) { blocked = block; };
	void SetValues(float parentValue, Vector2 goal);
	void SetParent(Vector2 parentNode) { parent = parentNode; };
	Vector2 GetParent() { return parent; };
	void ResetNode();
	float GetValueSofar() { return valueSofar; };
	float GetValueLeft() { return valueLeft; };
	float GetValueTotal() { return valueTotal; };

	void Draw();
	void RemoveFog() { fog = false; };

	// TODO: Add fog checker
};
