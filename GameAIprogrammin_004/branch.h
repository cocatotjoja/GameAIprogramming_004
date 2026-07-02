#pragma once
#include "globals.h"
#include "map.h"
#include "objects.h"
#include "StaffManager.h"


class Branch
{
public:
	Branch* childTrue = nullptr;
	Branch* childFalse = nullptr;

	virtual void WalkTree(Map& map, StaffManager& staff);
};

class WorkshopInventory : public Branch
{
public:
	WorkshopType shop;
	Product type;
	int ammount;

	WorkshopInventory(WorkshopType workshop, Product material, int number) : shop(workshop), type(material), ammount(number) {};
	void WalkTree(Map& map, StaffManager& staff);
};

class HaveWorkshop : public Branch
{
public:
	WorkshopType type;

	HaveWorkshop(WorkshopType newType) : type(newType) {};
	void WalkTree(Map& map, StaffManager& staff);
};

class HaveWorker : public Branch
{
	HaveWorker() {};
	void WalkTree(Map& map, StaffManager& staff);
};

class AvailableWorkshop : public Branch
{
	Branch* childWait = nullptr;
	Branch* childRunning = nullptr;
	WorkshopType type;
	AvailableWorkshop(WorkshopType newType) : type(newType) {};
	void WalkTree(Map& map, StaffManager& staff);

	void SetExtraChildren(Branch* waitChild, Branch* runningChild);
};

class AvailableWorker : public Branch
{
	AvailableWorker();
	void WalkTree(Map& map, StaffManager& staff);
};

class AvailableCrafter : public Branch
{
public:
	CrafterType type;

	AvailableCrafter(CrafterType newType) : type(newType) {};
	void WalkTree(Map& map, StaffManager& staff);
};