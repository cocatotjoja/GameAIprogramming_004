#pragma once

#include "globals.h"
#include "worker.h"

class StaffManager
{
private:
	Worker workers[50];
	Scout scouts[50];
	Soldier soldiers[50];
	Crafter crafters[50];

	int workerCount = 50;
	int scoutCount = 0;
	int soldierCount = 0;
	int crafterCount = 0;

public:
	StaffManager();

	void MakeScout();
	void MakeSoldier();
	void MakeCrafter(CrafterType type);

	void Update();
	void Draw();
	
	int GetNumWorkers() { return workerCount; };
	int AvailableWorker();
	bool AvailableCrafter(CrafterType type);

	void AssignWorkers(Product productType, WorkshopType workshopType, int numberNeeded);
	void AssignCrafter(CrafterType crafterType);
};