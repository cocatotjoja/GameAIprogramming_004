#pragma once
#include <random>
#include "raylib.h"


enum States
{
	HARVEST,
	TRANSPORT,
	CRAFTING,
	SCOUT,
	IDLE
};

enum Product
{
	WOOD,
	ORE,
	COAL,
	BAR,
	SWORD
};

enum WorkshopType
{
	COAL_MILL,
	SMELT,
	FORGE,
	TRAINING_CAMP
};

enum WorkshopState
{
	WAITING,
	RUNNING,
	AVAILABLE,
	NOT_BUILT
};

enum CrafterType
{
	MINER,
	SMITH,
	SMELTER,
	BUILDER
};

// Resolution Multiplier
static constexpr int resMult = 2;

//Window size
static float width = 1000 * resMult;
static float height = 1000 * resMult;
static float margin = 0;

//Project colors
static Color Mblack = { 54, 57, 59, 255 };
static Color Mwhite = { 250, 250, 250, 255 };
static Color Mgrey = { 240, 240, 240, 255 };
static Color Mgreen = { 176, 190, 162, 255 };
static Color MdarkGreen = { 40, 70, 70, 255 };
static Color Mblue = { 165, 216, 255, 255 };
static Color Mbrown = { 186, 155, 141, 255 };
static Color MdarkBrown = { 140, 117, 106, 255 };
static Color Mburgundy = { 111, 50, 60, 255 };
static Color Mred = { 250, 0, 0, 255 };


// Function for random int in a given range
inline int RandomIntRange(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}

inline Vector2 GetNearestNode(Vector2 currentPos)
{
	int x = (int)currentPos.x - (int)currentPos.x % (10 * resMult);
	int y = (int)currentPos.y - (int)currentPos.y % (10 * resMult);

	x = x/ (10 * resMult);
	y = y/ (10 * resMult);

	return Vector2{ (float)x, (float)y };
}
