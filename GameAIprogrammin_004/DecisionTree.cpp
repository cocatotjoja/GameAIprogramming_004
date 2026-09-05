#include "DecisionTree.h"

void DecisionTree::MakeTree()
{
	/*MAKE SOLDIER*/
	// [0] Have Camp
	branches.push_back(new HaveWorkshop(TRAINING_CAMP));
	// [1] Workshop Waiting
	branches.push_back(new WorkshopWaiting(TRAINING_CAMP));
	// [2] Have Sword
	branches.push_back(new WorkshopInventory(TRAINING_CAMP, SWORD, 1));
	// [3] Have Worker
	branches.push_back(new HaveWorker());
	// [4] Camp Available
	branches.push_back(new AvailableWorkshop(TRAINING_CAMP));
	// [5] ORDER SWORD
	branches.push_back(new OrderProduct(SWORD, TRAINING_CAMP, FORGE, 1));
	// [6] MAKE SOLDIER!
	branches.push_back(new StartProducing(TRAINING_CAMP, NO_CRAFTER, 60.0f));

	/*MAKE CAMP*/
	// [7] Workshop Waiting
	branches.push_back(new WorkshopWaiting(TRAINING_CAMP));
	// [8] Camp Wood > 10
	branches.push_back(new WorkshopInventory(TRAINING_CAMP, WOOD, 10));
	// [9] Have Builder - Has Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// [10] Have Builder - No Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// [11] Builder Available
	branches.push_back(new AvailableCrafter(BUILDER));
	// [12] ORDER WOOD
	branches.push_back(new GetMaterial(WOOD, TRAINING_CAMP, 10));
	// [13] MAKE BUILDER
	branches.push_back(new MakeCrafter(BUILDER));
	// [14] MAKE CAMP
	branches.push_back(new StartProducing(TRAINING_CAMP, BUILDER, 120.0f));

	/*MAKE SWORD*/
	// [15] Have Forge
	branches.push_back(new HaveWorkshop(FORGE));
	// [16] Any Orders
	branches.push_back(new CheckOrders(FORGE));
	// [17] Workshop Waiting
	branches.push_back(new WorkshopWaiting(FORGE));
	// [18] Forge Bar > 1
	branches.push_back(new WorkshopInventory(FORGE, BAR, 1));
	// [19] Forge Coal > 2 - No Bar
	branches.push_back(new WorkshopInventory(FORGE, COAL, 2));
	// [20] Have Smith - No Bar
	branches.push_back(new HaveCrafter(SMITH));
	// [21] Forge Coal > 2 - Has Bar
	branches.push_back(new WorkshopInventory(FORGE, COAL, 2));
	// [22] Have Smith - Has Bar
	branches.push_back(new HaveCrafter(SMITH));
	// [23] Forge Available
	branches.push_back(new AvailableWorkshop(FORGE));
	// [24] ORDER BAR
	branches.push_back(new OrderProduct(BAR, FORGE, SMELT, 1));
	// [25] ORDER COAL
	branches.push_back(new OrderProduct(COAL, FORGE, COAL_MILL, 2));
	// [26] MAKE SMITH!
	branches.push_back(new MakeCrafter(SMITH));
	// [27] MAKE SWORD!
	branches.push_back(new StartProducing(FORGE, SMITH, 60.0f));

	/*MAKE FORGE*/
	// [28] Workshop Waiting
	branches.push_back(new WorkshopWaiting(FORGE));
	// [29] Forge Bar > 3
	branches.push_back(new WorkshopInventory(FORGE, BAR, 3));
	// [30] Forge Wood > 10 - No Bar
	branches.push_back(new WorkshopInventory(FORGE, WOOD, 10));
	// [31] Have Builder - No Bar
	branches.push_back(new HaveCrafter(BUILDER));
	// [32] Forge Wood > 10 - Has Bar
	branches.push_back(new WorkshopInventory(FORGE, WOOD, 10));
	// [33] Have Builder - Has Bar
	branches.push_back(new HaveCrafter(BUILDER));
	// [34] Builder Available
	branches.push_back(new AvailableCrafter(BUILDER));
	// [35] GET WOOD
	branches.push_back(new GetMaterial(WOOD, FORGE, 10));
	// [36] ORDER BAR
	branches.push_back(new OrderProduct(BAR, FORGE, SMELT, 3));
	// [37] MAKE BUILDER!
	branches.push_back(new MakeCrafter(BUILDER));
	// [38] MAKE FORGE!
	branches.push_back(new StartProducing(FORGE, BUILDER, 180.0f));

	/*MAKE BAR*/
	// [39] Have Smelt
	branches.push_back(new HaveWorkshop(SMELT));
	// [40] Any Orders
	branches.push_back(new CheckOrders(SMELT));
	// [41] Workshop Waiting
	branches.push_back(new WorkshopWaiting(SMELT));
	// [42] Smelt Ore > 2
	branches.push_back(new WorkshopInventory(SMELT, ORE, 2));
	// [43] Smelt Coal > 3 - No Ore
	branches.push_back(new WorkshopInventory(SMELT, COAL, 3));
	// [44] Have Smelter - No Ore
	branches.push_back(new HaveCrafter(SMELTER));
	// [45] Smelt Coal > 3 - Has Ore
	branches.push_back(new WorkshopInventory(SMELT, COAL, 3));
	// [46] Have Smelter - Has Ore
	branches.push_back(new HaveCrafter(SMELTER));
	// [47] Smelt Available
	branches.push_back(new AvailableWorkshop(SMELT));
	// [48] GET ORE
	branches.push_back(new GetMaterial(ORE, SMELT, 2));
	// [49] ORDER COAL
	branches.push_back(new OrderProduct(COAL, SMELT, COAL_MILL, 3));
	// [50] MAKE SMELTER!
	branches.push_back(new MakeCrafter(SMELTER));
	// [51] MAKE BAR!
	branches.push_back(new StartProducing(SMELT, SMELTER, 30.0f));

	/*MAKE SMELT*/
	// [52] Workshop Waiting
	branches.push_back(new WorkshopWaiting(SMELT));
	// [53] Smelt Wood > 10
	branches.push_back(new WorkshopInventory(SMELT, WOOD, 10));
	// [54] Have Builder - No Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// [55] Have Builder - Has Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// [56] Builder Available
	branches.push_back(new AvailableCrafter(BUILDER));
	// [57] GET WOOD
	branches.push_back(new GetMaterial(WOOD, SMELT, 10));
	// [58] MAKE BUILDER!
	branches.push_back(new MakeCrafter(BUILDER));
	// [59] MAKE SMELT!
	branches.push_back(new StartProducing(SMELT, BUILDER, 120.0f));

	/*MAKE COAL*/
	// [60] Have Mill
	branches.push_back(new HaveWorkshop(COAL_MILL));
	// [61] Any Orders
	branches.push_back(new CheckOrders(COAL_MILL));
	// [62] Workshop Waiting
	branches.push_back(new WorkshopWaiting(COAL_MILL));
	// [63] Mill Wood > 2
	branches.push_back(new WorkshopInventory(COAL_MILL, WOOD, 2));
	// [64] Have Miner - No Wood
	branches.push_back(new HaveCrafter(MINER));
	// [65] Have Miner - Has Wood
	branches.push_back(new HaveCrafter(MINER));
	// [66] Mill Available
	branches.push_back(new AvailableWorkshop(COAL_MILL));
	// [67] GET WOOD
	branches.push_back(new GetMaterial(WOOD, COAL_MILL, 2));
	// [68] MAKE MINER!
	branches.push_back(new MakeCrafter(MINER));
	// [69] MAKE COAL!
	branches.push_back(new StartProducing(COAL_MILL, MINER, 30.0f));

	/*MAKE MILL*/
	// [70] Workshop Waiting
	branches.push_back(new WorkshopWaiting(COAL_MILL));
	// [71] Mill Wood > 10
	branches.push_back(new WorkshopInventory(COAL_MILL, WOOD, 10));
	// [72] Have Builder - No Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// [73] Have Builder - Has Wood
	branches.push_back(new HaveCrafter(BUILDER));
	// [74] Builder Available
	branches.push_back(new AvailableCrafter(BUILDER));
	// [75] GET WOOD
	branches.push_back(new GetMaterial(WOOD, COAL_MILL, 10));
	// [76] MAKE BUILDER!
	branches.push_back(new MakeCrafter(BUILDER));
	// [77] MAKE MILL!
	branches.push_back(new StartProducing(COAL_MILL, BUILDER, 60.0f));



	// [78]  /*END!*/
	branches.push_back(new EndPoint());



	// Set Children

	/*MAKE SOLDIER*/
	branches[0]->SetChildren(branches[1], branches[7]);
	branches[1]->SetChildren(branches[15], branches[2]);
	branches[2]->SetChildren(branches[3], branches[5]);
	branches[3]->SetChildren(branches[4], branches[78]);
	branches[4]->SetChildren(branches[6], branches[15]);
	branches[5]->SetChildren(branches[15], branches[15]);
	branches[6]->SetChildren(branches[15], branches[15]);

	/*MAKE CAMP*/
	branches[7]->SetChildren(branches[15], branches[8]);
	branches[8]->SetChildren(branches[9], branches[12]);
	branches[9]->SetChildren(branches[11], branches[13]);
	branches[10]->SetChildren(branches[15], branches[13]);
	branches[11]->SetChildren(branches[14], branches[15]);
	branches[12]->SetChildren(branches[10], branches[10]);
	branches[13]->SetChildren(branches[15], branches[15]);
	branches[14]->SetChildren(branches[15], branches[15]);

	/*MAKE SWORD*/
	branches[15]->SetChildren(branches[16], branches[28]);
	branches[16]->SetChildren(branches[17], branches[39]);
	branches[17]->SetChildren(branches[39], branches[18]);
	branches[18]->SetChildren(branches[21], branches[24]);
	branches[19]->SetChildren(branches[20], branches[25]);
	branches[20]->SetChildren(branches[39], branches[26]);
	branches[21]->SetChildren(branches[22], branches[25]);
	branches[22]->SetChildren(branches[23], branches[26]);
	branches[23]->SetChildren(branches[27], branches[39]);
	branches[24]->SetChildren(branches[19], branches[19]);
	branches[25]->SetChildren(branches[20], branches[20]);
	branches[26]->SetChildren(branches[39], branches[39]);
	branches[27]->SetChildren(branches[39], branches[39]);

	/*MAKE FORGE*/
	branches[28]->SetChildren(branches[39], branches[29]);
	branches[29]->SetChildren(branches[32], branches[36]);
	branches[30]->SetChildren(branches[31], branches[35]);
	branches[31]->SetChildren(branches[39], branches[37]);
	branches[32]->SetChildren(branches[33], branches[35]);
	branches[33]->SetChildren(branches[34], branches[37]);
	branches[34]->SetChildren(branches[38], branches[39]);
	branches[35]->SetChildren(branches[31], branches[31]);
	branches[36]->SetChildren(branches[30], branches[30]);
	branches[37]->SetChildren(branches[39], branches[39]);
	branches[38]->SetChildren(branches[39], branches[39]);

	/*MAKE BAR*/
	branches[39]->SetChildren(branches[40], branches[52]);
	branches[40]->SetChildren(branches[41], branches[60]);
	branches[41]->SetChildren(branches[60], branches[42]);
	branches[42]->SetChildren(branches[45], branches[48]);
	branches[43]->SetChildren(branches[44], branches[49]);
	branches[44]->SetChildren(branches[60], branches[50]);
	branches[45]->SetChildren(branches[46], branches[49]);
	branches[46]->SetChildren(branches[47], branches[40]);
	branches[47]->SetChildren(branches[51], branches[60]);
	branches[48]->SetChildren(branches[43], branches[43]);
	branches[49]->SetChildren(branches[44], branches[44]);
	branches[50]->SetChildren(branches[60], branches[60]);
	branches[51]->SetChildren(branches[60], branches[60]);

	/*MAKE SMELT*/
	branches[52]->SetChildren(branches[60], branches[53]);
	branches[53]->SetChildren(branches[55], branches[57]);
	branches[54]->SetChildren(branches[60], branches[58]);
	branches[55]->SetChildren(branches[56], branches[58]);
	branches[56]->SetChildren(branches[59], branches[60]);
	branches[57]->SetChildren(branches[54], branches[54]);
	branches[58]->SetChildren(branches[60], branches[60]);
	branches[59]->SetChildren(branches[60], branches[60]);

	/*MAKE COAL*/
	branches[60]->SetChildren(branches[61], branches[70]);
	branches[61]->SetChildren(branches[62], branches[78]);
	branches[62]->SetChildren(branches[78], branches[63]);
	branches[63]->SetChildren(branches[65], branches[67]);
	branches[64]->SetChildren(branches[78], branches[68]);
	branches[65]->SetChildren(branches[66], branches[68]);
	branches[66]->SetChildren(branches[69], branches[78]);
	branches[67]->SetChildren(branches[64], branches[64]);
	branches[68]->SetChildren(branches[78], branches[78]);
	branches[69]->SetChildren(branches[78], branches[78]);

	/*MAKE MILL*/
	branches[70]->SetChildren(branches[78], branches[71]);
	branches[71]->SetChildren(branches[73], branches[75]);
	branches[72]->SetChildren(branches[78], branches[76]);
	branches[73]->SetChildren(branches[74], branches[76]);
	branches[74]->SetChildren(branches[77], branches[78]);
	branches[75]->SetChildren(branches[72], branches[72]);
	branches[76]->SetChildren(branches[78], branches[78]);
	branches[77]->SetChildren(branches[78], branches[78]);
}

DecisionTree::DecisionTree(Map* newMap, StaffManager* newStaff)
{
	map = newMap;
	staff = newStaff;
}

void DecisionTree::WalkTree()
{
}
