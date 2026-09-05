#pragma once
#include "globals.h"
#include "map.h"
#include "objects.h"
#include "StaffManager.h"

// Decision Brances
class Branch
{
public:
	Branch* childTrue = nullptr;
	Branch* childFalse = nullptr;

	virtual void WalkTree(Map& map, StaffManager& staff) {}
	void SetChildren(Branch* t, Branch* f);
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
public:
	HaveWorker() {};
	void WalkTree(Map& map, StaffManager& staff);
};

class HaveCrafter : public Branch
{
public:
	CrafterType type;
	HaveCrafter(CrafterType newType) : type(newType) {};
	void WalkTree(Map& map, StaffManager& staff);
};

class AvailableWorkshop : public Branch
{
public:
	WorkshopType type;
	AvailableWorkshop(WorkshopType newType) : type(newType) {};
	void WalkTree(Map& map, StaffManager& staff);
};

class AvailableCrafter : public Branch
{
public:
	CrafterType type;

	AvailableCrafter(CrafterType newType) : type(newType) {};
	void WalkTree(Map& map, StaffManager& staff);
};

class WorkshopWaiting : public Branch
{
public:
	WorkshopType type;
	WorkshopWaiting(WorkshopType newType) : type(newType) {};
	void WalkTree(Map& map, StaffManager& staff);
};

class CheckOrders : public Branch
{
public:
	WorkshopType type;
	CheckOrders(WorkshopType newType) : type(newType) {};
	void WalkTree(Map& map, StaffManager& staff);
};


// Action Branches
class OrderProduct : public Branch
{
public:
	Product type;
	WorkshopType workshop;
	WorkshopType producer;
	int neededAmount;

	OrderProduct(Product newType, WorkshopType newWorkshop, WorkshopType newProducer, int amount) : type(newType), workshop(newWorkshop), producer(newProducer), neededAmount(amount) {};
	void WalkTree(Map& map, StaffManager& staff);
};

class MakeCrafter : public Branch
{
public:
	CrafterType type;

	MakeCrafter(CrafterType newType) : type(newType) {};
	void WalkTree(Map& map, StaffManager& staff);
};

class GetMaterial : public Branch
{
public:
	Product type;
	WorkshopType workshop;
	int neededAmount;

	GetMaterial(Product newType, WorkshopType newWorkshop, int amount) : type(newType), workshop(newWorkshop), neededAmount(amount) {};
	void WalkTree(Map& map, StaffManager& staff);
};

class StartProducing : public Branch
{
public:
	WorkshopType type;
	CrafterType crafter;
	float craftingTime;

	StartProducing(WorkshopType newType, CrafterType newCrafter, float newTime) : type(newType), crafter(newCrafter), craftingTime() {};
	void WalkTree(Map& map, StaffManager& staff);
};

class EndPoint : public Branch
{
public:
	EndPoint() {};
	void WalkTree(Map& map, StaffManager& staff) { return; };
};
