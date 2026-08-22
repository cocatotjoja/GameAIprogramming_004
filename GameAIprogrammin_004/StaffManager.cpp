#include "StaffManager.h"

StaffManager::StaffManager(Map* newMap)
{
	map = newMap;

	// Create workers
	for (size_t i = 0; i < 50; i++)
	{
		int x = 21;
		int y = 36;

		x += RandomIntRange(2, (90*resMult)-2 );
		y += RandomIntRange(2, (90*resMult)-2 );

		workers.push_back(Worker({ (float)x, (float)y }, map));
	}
}

void StaffManager::MakeScout()
{
	Vector2 quad = { 0,0 };
	Vector2 pos = workers.back().position;
	scouts.push_back(Scout(quad, pos, map));

	workers.pop_back();
}

void StaffManager::Update()
{
	for (Worker w : workers)
	{
		w.Update();
	}

	for (Scout s : scouts)
	{
		s.Update();
	}

	for (Crafter c : crafters)
	{
		c.Update();
	}

	for (Soldier sl : soldiers)
	{
		sl.Update();
	}
}

void StaffManager::Draw()
{
	for (Worker w : workers)
	{
		w.Draw();
	}

	for (Scout s : scouts)
	{
		s.Draw();
	}

	for (Crafter c : crafters)
	{
		c.Draw();
	}

	for (Soldier sl : soldiers)
	{
		sl.Draw();
	}
}

int StaffManager::AvailableWorker()
{
	int availableWorkers = 0;
	for (Worker w : workers)
	{
		if (w.IsFree())
		{
			availableWorkers++;
		}
	}
    return availableWorkers;
}

bool StaffManager::AvailableCrafter(CrafterType type)
{
	for (Crafter c : crafters)
	{
		if (c.GetType() == type && c.IsFree())
		{
			return true;
		}
	}
    return false;
}

void StaffManager::AssignWorkers(Product productType, WorkshopType workshopType, int numberNeeded)
{
	// Assign correct number of workers
	int index = 0;
	int assigned = 0;
	while (index < 50 && assigned < numberNeeded)
	{
		if (workers[index].IsFree())
		{
			// Assign worker
			workers[index].GetProduct(productType, workshopType);
			assigned++;
		}
		index++;
	}
}

void StaffManager::AssignCrafter(CrafterType crafterType)
{
	for (size_t i = 0; i < 50; i++)
	{
		if (crafters[i].GetType() == crafterType && crafters[i].IsFree())
		{
			// Set crafter to working
			crafters[i].GetCrafting();
		}
	}
}
