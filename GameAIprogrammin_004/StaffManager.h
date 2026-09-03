#pragma once

#include <vector>
#include "globals.h"
#include "worker.h"

class Map;

class StaffManager
{
private:
	Map* map;
	std::vector<Worker> workers;
	std::vector<Scout> scouts;
	std::vector<Soldier> soldiers;
	std::vector<Crafter> crafters;

public:
	StaffManager(Map* newMap);

	void MakeScout();
	void MakeSoldier();
	void MakeCrafter(CrafterType type);

	void Update();
	void Draw();
	
	int GetNumWorkers() { return workers.size(); };
	int AvailableWorker();
	bool AvailableCrafter(CrafterType type);
	bool HaveCrafter(CrafterType type);

	void AssignWorkers(Product productType, WorkshopType workshopType, int numberNeeded);
	void AssignCrafter(CrafterType crafterType, float newTime);
};