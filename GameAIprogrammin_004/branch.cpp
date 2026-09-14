#include <iostream>

#include "branch.h"



void Branch::SetChildren(Branch* t, Branch* f)
{
	childTrue = t;
	childFalse = f;
}


void WorkshopInventory::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;

	Workshop* thisWorkshop = map.GetWorkshop(shop);

	if (thisWorkshop->CheckInventory(type) >= ammount)
	{
		std::cout << "True" << std::endl;

		childTrue->WalkTree(map, staff);
	}
	else
	{
		std::cout << "False" << std::endl;

		childFalse->WalkTree(map, staff);
	}
}

void HaveWorkshop::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;

	Workshop* thisWorkshop = map.GetWorkshop(type);

	if (thisWorkshop->IsBuilt() == true)
	{
		std::cout << "True" << std::endl;

		childTrue->WalkTree(map, staff);
	}
	else
	{
		std::cout << "False" << std::endl;

		childFalse->WalkTree(map, staff);
	}
}

void HaveWorker::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;

	if (staff.GetNumWorkers() > 0)
	{
		std::cout << "True" << std::endl;

		childTrue->WalkTree(map, staff);
	}
	else
	{
		std::cout << "False" << std::endl;

		childFalse->WalkTree(map, staff);
	}
}

void HaveCrafter::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;

	if (staff.HaveCrafter(type))
	{
		std::cout << "True" << std::endl;

		childTrue->WalkTree(map, staff);
	}
	else
	{
		std::cout << "False" << std::endl;

		childFalse->WalkTree(map, staff);
	}
}

void AvailableWorkshop::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;

	Workshop* thisWorkshop = map.GetWorkshop(type);

	if (thisWorkshop->GetState() == AVAILABLE)
	{
		std::cout << "True" << std::endl;

		childTrue->WalkTree(map, staff);
	}
	else
	{
		std::cout << "False" << std::endl;

		childFalse->WalkTree(map, staff);
	}
}

void AvailableCrafter::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;

	if (staff.AvailableCrafter(type))
	{
		std::cout << "True" << std::endl;

		childTrue->WalkTree(map, staff);
	}
	else
	{
		std::cout << "False" << std::endl;

		childFalse->WalkTree(map, staff);
	}
}

void WorkshopWaiting::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;

	Workshop* thisWorkshop = map.GetWorkshop(type);

	WorkshopState currentState = thisWorkshop->GetState();
	if (currentState == WAITING || currentState == RUNNING)
	{
		std::cout << "True" << std::endl;

		childTrue->WalkTree(map, staff);
	}
	else
	{
		std::cout << "False" << std::endl;

		childFalse->WalkTree(map, staff);
	}
}

void CheckOrders::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;

	Workshop* thisWorkshop = map.GetWorkshop(type);

	int numOrders = thisWorkshop->CheckOrders();
	if (numOrders > 0)
	{
		std::cout << "True" << std::endl;

		childTrue->WalkTree(map, staff);
	}
	else
	{
		std::cout << "False" << std::endl;

		childFalse->WalkTree(map, staff);
	}
}

void OrderProduct::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;

	Workshop* thisWorkshop = map.GetWorkshop(workshop);

	// Calculate Ammount needed
	int currentAmount = thisWorkshop->CheckInventory(type);
	int calculatedAmount = neededAmount - currentAmount;


	// Order Product
	Workshop* thisProducer = map.GetWorkshop(producer);
	thisProducer->PlaceOrder(calculatedAmount);

	// Assign Worker
	staff.AssignWorkers(type, workshop, calculatedAmount);

	// Set Workshop to waiting
	thisWorkshop->SetState(WAITING);

	// Walk
	childTrue->WalkTree(map, staff);
}

void MakeCrafter::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;

	staff.MakeCrafter(type);

	// Walk
	childTrue->WalkTree(map, staff);
}

void GetMaterial::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;
	
	Workshop* thisWorkshop = map.GetWorkshop(workshop);

	// Calculate Ammount needed
	int currentAmount = thisWorkshop->CheckInventory(type);
	int calculatedAmount = neededAmount - currentAmount;

	// Assign Worker
	staff.AssignWorkers(type, workshop, calculatedAmount);

	// Set Workshop to waiting
	thisWorkshop->SetState(WAITING);

	// Walk
	childTrue->WalkTree(map, staff);
}

void StartProducing::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;
	
	Workshop* thisWorkshop = map.GetWorkshop(type);
	thisWorkshop->SetState(RUNNING);
	thisWorkshop->UseMaterials();
	staff.AssignCrafter(crafter, craftingTime);

	// Walk
	childTrue->WalkTree(map, staff);
}


void EndPoint::WalkTree(Map& map, StaffManager& staff)
{
	std::cout << branchDef << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	return;
}
