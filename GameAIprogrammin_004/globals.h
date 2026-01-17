#pragma once
#include <random>
#include "raylib.h"

// Resolution Multiplier
static int resMult = 2;

//Project colors
static Color Mblack = { 54, 57, 59, 255 };
static Color Mwhite = { 250, 250, 250, 255 };
static Color Mgreen = { 176, 190, 162, 255 };
static Color MdarkGreen = { 40, 70, 70, 255 };
static Color Mblue = { 165, 216, 255, 255 };
static Color Mbrown = { 186, 155, 141, 255 };
static Color MdarkBrown = { 140, 117, 106, 255 };
static Color Mburgundy = { 111, 50, 60, 255 };


// Function for random int in a given range
inline int RandomIntRange(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
