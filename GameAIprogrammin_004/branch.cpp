#include "branch.h"

void WorkshopInventory::WalkTree(Map& map, StaffManager& staff)
{
	if (map.GetWorkshop(shop)->CheckInventory(type) >= ammount)
	{
		childTrue->WalkTree(map, staff);
	}
	else
	{
		childFalse->WalkTree(map, staff);
	}
}

void HaveWorkshop::WalkTree(Map& map, StaffManager& staff)
{
	if (map.HaveWorkshop(type))
	{
		childTrue->WalkTree(map, staff);
	}
	else
	{
		childFalse->WalkTree(map, staff);
	}
}

void HaveWorker::WalkTree(Map& map, StaffManager& staff)
{
	if (staff.GetNumWorkers() > 0)
	{
		childTrue->WalkTree(map, staff);
	}
	else
	{
		childFalse->WalkTree(map, staff);
	}
}

void HaveCrafter::WalkTree(Map& map, StaffManager& staff)
{
	if (staff.HaveCrafter(type))
	{
		childTrue->WalkTree(map, staff);
	}
	else
	{
		childFalse->WalkTree(map, staff);
	}
}

void AvailableWorkshop::WalkTree(Map& map, StaffManager& staff)
{
	if (map.GetWorkshop(type)->GetState() == AVAILABLE)
	{
		childTrue->WalkTree(map, staff);
	}
	else
	{
		childFalse->WalkTree(map, staff);
	}
}

void AvailableCrafter::WalkTree(Map& map, StaffManager& staff)
{
	if (staff.AvailableCrafter(type))
	{
		childTrue->WalkTree(map, staff);
	}
	else
	{
		childFalse->WalkTree(map, staff);
	}
}

void WorkshopWaiting::WalkTree(Map& map, StaffManager& staff)
{
	if (map.GetWorkshop(type)->GetState() == WAITING)
	{
		childTrue->WalkTree(map, staff);
	}
	else
	{
		childFalse->WalkTree(map, staff);
	}
}

void CheckOrders::WalkTree(Map& map, StaffManager& staff)
{
	if (map.GetWorkshop(type)->CheckOrders() > 0)
	{
		childTrue->WalkTree(map, staff);
	}
	else
	{
		childFalse->WalkTree(map, staff);
	}
}

void OrderProduct::WalkTree(Map& map, StaffManager& staff)
{
	// Calculate Ammount needed
	int currentAmount = map.GetWorkshop(workshop)->CheckInventory(type);
	int calculatedAmount = neededAmount - currentAmount;

	// Order Product TODO: Wrong workshop here
	map.GetWorkshop(producer)->PlaceOrder(calculatedAmount);

	// Assign Worker
	staff.AssignWorkers(type, workshop, calculatedAmount);

	// Set Workshop to waiting
	map.GetWorkshop(workshop)->SetState(WAITING);

	// Walk
	childTrue->WalkTree(map, staff);
}

void MakeCrafter::WalkTree(Map& map, StaffManager& staff)
{
	staff.MakeCrafter(type);

	// Walk
	childTrue->WalkTree(map, staff);
}

void GetMaterial::WalkTree(Map& map, StaffManager& staff)
{
	// Calculate Ammount needed
	int currentAmount = map.GetWorkshop(workshop)->CheckInventory(type);
	int calculatedAmount = neededAmount - currentAmount;

	// Assign Worker
	staff.AssignWorkers(type, workshop, calculatedAmount);

	// Set Workshop to waiting
	map.GetWorkshop(workshop)->SetState(WAITING);

	// Walk
	childTrue->WalkTree(map, staff);
}

void StartProducing::WalkTree(Map& map, StaffManager& staff)
{
	map.GetWorkshop(type)->SetState(RUNNING);
	staff.AssignCrafter(crafter, craftingTime);

	// Walk
	childTrue->WalkTree(map, staff);
}

void Branch::SetChildren(Branch* t, Branch* f)
{
	childTrue = t;
	childFalse = f;
}
