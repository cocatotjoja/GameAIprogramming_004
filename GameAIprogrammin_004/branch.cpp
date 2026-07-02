#include "branch.h"

void WorkshopInventory::WalkTree(Map& map, StaffManager& staff)
{
	if (map.GetWorkshop(shop)->CheckInventory(type) < ammount)
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
	if (map.GetWorkshop(type) != nullptr)
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

void AvailableWorkshop::WalkTree(Map& map, StaffManager& staff)
{
	if (map.GetWorkshop(type)->GetState() == AVAILABLE)
	{
		childTrue->WalkTree(map, staff);
	}
	else if (map.GetWorkshop(type)->GetState() == WAITING)
	{
		childWait->WalkTree(map, staff);
	}
	else if (map.GetWorkshop(type)->GetState() == RUNNING)
	{
		childRunning->WalkTree(map, staff);
	}
	else
	{
		childFalse->WalkTree(map, staff);
	}
}

void AvailableWorkshop::SetExtraChildren(Branch* waitChild, Branch* runningChild)
{
	childWait = waitChild;
	childRunning = runningChild;
}

void AvailableWorker::WalkTree(Map& map, StaffManager& staff)
{
	if (staff.AvailableWorker())
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
