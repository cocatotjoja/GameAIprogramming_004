#include "DecisionTree.h"

void DecisionTree::MakeTree()
{
	/*MAKE SOLDIER*/
	// Have Camp
	branches.push_back(new HaveWorkshop(TRAINING_CAMP));
	// Workshop Waiting
	branches.push_back(new WorkshopWaiting(TRAINING_CAMP));
	// Have Sword
	branches.push_back(new WorkshopInventory(TRAINING_CAMP, SWORD, 1));
	// Have Worker
	branches.push_back(new HaveWorker());
	// Camp Available
	branches.push_back(new AvailableWorkshop(TRAINING_CAMP));
	// ORDER SWORD
	branches.push_back(new OrderProduct(SWORD, TRAINING_CAMP, 1));
	// MAKE SOLDIER!
	branches.push_back(new StartProducing(TRAINING_CAMP, NO_CRAFTER, 60.0f));

	/*MAKE CAMP*/
	// Workshop Waiting
	branches.push_back(new WorkshopWaiting(TRAINING_CAMP));
	// Camp Wood > 10
	branches.push_back(new WorkshopInventory(TRAINING_CAMP, WOOD, 10));
	// Have Builder - Has Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// Have Builder - No Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// Builder Available
	branches.push_back(new AvailableCrafter(BUILDER));
	// Have Builder
	branches.push_back(new HaveCrafter(BUILDER));
	// ORDER WOOD
	branches.push_back(new OrderProduct(WOOD, TRAINING_CAMP, 10));
	// MAKE BUILDER
	branches.push_back(new MakeCrafter(BUILDER));
	// MAKE CAMP
	branches.push_back(new StartProducing(TRAINING_CAMP, BUILDER, 120.0f));

	/*MAKE SWORD*/
	// Have Forge
	branches.push_back(new HaveWorkshop(FORGE));
	// Any Orders
	branches.push_back(new CheckOrders(FORGE));
	// Workshop Waiting
	branches.push_back(new WorkshopWaiting(FORGE));
	// Forge Bar > 1
	branches.push_back(new WorkshopInventory(FORGE, BAR, 1));
	// Forge Coal > 2 - No Bar
	branches.push_back(new WorkshopInventory(FORGE, COAL, 2));
	// Have Smith - No Bar
	branches.push_back(new HaveCrafter(SMITH));
	// Forge Coal > 2 - Has Bar
	branches.push_back(new WorkshopInventory(FORGE, COAL, 2));
	// Have Smith - Has Bar
	branches.push_back(new HaveCrafter(SMITH));
	// Forge Available
	branches.push_back(new AvailableWorkshop(FORGE));
	// ORDER BAR
	branches.push_back(new OrderProduct(BAR, FORGE, 1));
	// ORDER COAL
	branches.push_back(new OrderProduct(COAL, FORGE, 2));
	// MAKE SMITH!
	branches.push_back(new MakeCrafter(SMITH));
	// MAKE SWORD!
	branches.push_back(new StartProducing(FORGE, SMITH, 60.0f));

	/*MAKE FORGE*/
	// Workshop Waiting
	branches.push_back(new WorkshopWaiting(FORGE));
	// Forge Bar > 3
	branches.push_back(new WorkshopInventory(FORGE, BAR, 3));
	// Forge Wood > 10 - No Bar
	branches.push_back(new WorkshopInventory(FORGE, WOOD, 10));
	// Have Builder - No Bar
	branches.push_back(new HaveCrafter(BUILDER));
	// Forge Wood > 10 - Has Bar
	branches.push_back(new WorkshopInventory(FORGE, WOOD, 10));
	// Have Builder - Has Bar
	branches.push_back(new HaveCrafter(BUILDER));
	// Builder Available
	branches.push_back(new AvailableCrafter(BUILDER));
	// GET WOOD
	branches.push_back(new GetMaterial(WOOD, FORGE, 10));
	// ORDER BAR
	branches.push_back(new OrderProduct(BAR, FORGE, 3));
	// MAKE BUILDER!
	branches.push_back(new MakeCrafter(BUILDER));
	// MAKE FORGE!
	branches.push_back(new StartProducing(FORGE, BUILDER, 180.0f));

	/*MAKE BAR*/
	// Have Smelt
	branches.push_back(new HaveWorkshop(SMELT));
	// Any Orders
	branches.push_back(new CheckOrders(SMELT));
	// Workshop Waiting
	branches.push_back(new WorkshopWaiting(SMELT));
	// Smelt Ore > 2
	branches.push_back(new WorkshopInventory(SMELT, ORE, 2));
	// Smelt Coal > 3 - No Ore
	branches.push_back(new WorkshopInventory(SMELT, COAL, 3));
	// Have Smelter - No Ore
	branches.push_back(new HaveCrafter(SMELTER));
	// Smelt Coal > 3 - Has Ore
	branches.push_back(new WorkshopInventory(SMELT, COAL, 3));
	// Have Smelter - Has Ore
	branches.push_back(new HaveCrafter(SMELTER));
	// Smelt Available
	branches.push_back(new AvailableWorkshop(SMELT));
	// GET ORE
	branches.push_back(new GetMaterial(ORE, SMELT, 2));
	// ORDER COAL
	branches.push_back(new OrderProduct(COAL, SMELT, 3));
	// MAKE SMELTER!
	branches.push_back(new MakeCrafter(SMELTER));
	// MAKE BAR!
	branches.push_back(new StartProducing(SMELT, SMELTER, 30.0f));

	/*MAKE SMELT*/
	// Workshop Waiting
	branches.push_back(new WorkshopWaiting(SMELT));
	// Smelt Wood > 10
	branches.push_back(new WorkshopInventory(SMELT, WOOD, 10));
	// Have Builder - No Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// Have Builder - Has Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// Builder Available
	branches.push_back(new AvailableCrafter(BUILDER));
	// GET WOOD
	branches.push_back(new GetMaterial(WOOD, SMELT, 10));
	// MAKE BUILDER!
	branches.push_back(new MakeCrafter(BUILDER));
	// MAKE SMELT!
	branches.push_back(new StartProducing(SMELT, BUILDER, 120.0f));

	/*MAKE COAL*/
	// Have Mill
	branches.push_back(new HaveWorkshop(COAL_MILL));
	// Any Orders
	branches.push_back(new CheckOrders(COAL_MILL));
	// Workshop Waiting
	branches.push_back(new WorkshopWaiting(COAL_MILL));
	// Mill Wood > 2
	branches.push_back(new WorkshopInventory(COAL_MILL, WOOD, 2));
	// Have Miner - No Wood
	branches.push_back(new HaveCrafter(MINER));
	// Have Miner - Has Wood
	branches.push_back(new HaveCrafter(MINER));
	// Mill Available
	branches.push_back(new AvailableWorkshop(COAL_MILL));
	// GET WOOD
	branches.push_back(new GetMaterial(WOOD, COAL_MILL, 2));
	// MAKE MINER!
	branches.push_back(new MakeCrafter(MINER));
	// MAKE COAL!
	branches.push_back(new StartProducing(COAL_MILL, MINER, 30.0f));

	/*MAKE MILL*/
	// Workshop Waiting
	branches.push_back(new WorkshopWaiting(COAL_MILL));
	// Mill Wood > 10
	branches.push_back(new WorkshopInventory(COAL_MILL, WOOD, 10));
	// Have Builder - No Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// Have Builder - Has Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// Builder Available
	branches.push_back(new AvailableCrafter(BUILDER));
	// GET WOOD
	branches.push_back(new GetMaterial(WOOD, COAL_MILL, 10));
	// MAKE BUILDER!
	branches.push_back(new MakeCrafter(BUILDER));
	// MAKE MILL!
	branches.push_back(new StartProducing(COAL_MILL, BUILDER, 60.0f));



	/*END!*/
	branches.push_back(new EndPoint());
}

DecisionTree::DecisionTree(Map* newMap, StaffManager* newStaff)
{
	map = newMap;
	staff = newStaff;
}

void DecisionTree::WalkTree()
{
}
