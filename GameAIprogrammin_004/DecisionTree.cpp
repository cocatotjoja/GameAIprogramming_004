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
	branches[78]->SetString("78. END!");





	// Set Children

	/*MAKE SOLDIER*/
	// [0] Have Camp
	branches[0]->SetString("0. Is camp built?");
	branches[0]->SetChildren(branches[1], branches[7]);
	// [1] Workshop Waiting
	branches[1]->SetString("1. Is camp Waiting?");
	branches[1]->SetChildren(branches[15], branches[2]);
	// [2] Have Sword
	branches[2]->SetString("2. Does camp have 1 sword?");
	branches[2]->SetChildren(branches[3], branches[5]);
	// [3] Have Worker
	branches[3]->SetString("3. Are there any worksers left?");
	branches[3]->SetChildren(branches[4], branches[78]);
	// [4] Camp Available
	branches[4]->SetString("4. Is the camp available?");
	branches[4]->SetChildren(branches[6], branches[15]);
	// [5] ORDER SWORD
	branches[5]->SetString("5. Order sword for camp!");
	branches[5]->SetChildren(branches[15], branches[15]);
	// [6] MAKE SOLDIER!
	branches[6]->SetString("6. Make a soldier!");
	branches[6]->SetChildren(branches[15], branches[15]);

	/*MAKE CAMP*/
	// [7] Workshop Waiting
	branches[7]->SetString("7. Is camp waiting?");
	branches[7]->SetChildren(branches[15], branches[8]);
	// [8] Camp Wood > 10
	branches[8]->SetString("8. Does camp have 10 wood?");
	branches[8]->SetChildren(branches[9], branches[12]);
	// [9] Have Builder - Has Wood
	branches[9]->SetString("9. Is there a builder?");
	branches[9]->SetChildren(branches[11], branches[13]);
	// [10] Have Builder - No Wood
	branches[10]->SetString("10. Is there a builder?");
	branches[10]->SetChildren(branches[15], branches[13]);
	// [11] Builder Available
	branches[11]->SetString("11. Is builder available?");
	branches[11]->SetChildren(branches[14], branches[15]);
	// [12] ORDER WOOD
	branches[12]->SetString("12. Get wood for camp!");
	branches[12]->SetChildren(branches[10], branches[10]);
	// [13] MAKE BUILDER
	branches[13]->SetString("13. Make a builder!");
	branches[13]->SetChildren(branches[15], branches[15]);
	// [14] MAKE CAMP
	branches[14]->SetString("14. Make a camp!");
	branches[14]->SetChildren(branches[15], branches[15]);

	/*MAKE SWORD*/
	// [15] Have Forge
	branches[15]->SetString("15. Is forge built?");
	branches[15]->SetChildren(branches[16], branches[28]);
	// [16] Any Orders
	branches[16]->SetString("16. Does forge have orders?");
	branches[16]->SetChildren(branches[17], branches[39]);
	// [17] Workshop Waiting
	branches[17]->SetString("17. Is forge waiting?");
	branches[17]->SetChildren(branches[39], branches[18]);
	// [18] Forge Bar > 1
	branches[18]->SetString("18. Does forge have 1 bar?");
	branches[18]->SetChildren(branches[21], branches[24]);
	// [19] Forge Coal > 2 - No Bar
	branches[19]->SetString("19. Does forge have 2 coal?");
	branches[19]->SetChildren(branches[20], branches[25]);
	// [20] Have Smith - No Bar
	branches[20]->SetString("20. Is there a smith?");
	branches[20]->SetChildren(branches[39], branches[26]);
	// [21] Forge Coal > 2 - Has Bar
	branches[21]->SetString("21. Does forge have 2 coal?");
	branches[21]->SetChildren(branches[22], branches[25]);
	// [22] Have Smith - Has Bar
	branches[22]->SetString("22. Is there a smith?");
	branches[22]->SetChildren(branches[23], branches[26]);
	// [23] Forge Available
	branches[23]->SetString("23. Is forge available?");
	branches[23]->SetChildren(branches[27], branches[39]);
	// [24] ORDER BAR
	branches[24]->SetString("24. Order bar for forge!");
	branches[24]->SetChildren(branches[19], branches[19]);
	// [25] ORDER COAL
	branches[25]->SetString("25. Order coal for forge!");
	branches[25]->SetChildren(branches[20], branches[20]);
	// [26] MAKE SMITH!
	branches[26]->SetString("26. Make a smith!");
	branches[26]->SetChildren(branches[39], branches[39]);
	// [27] MAKE SWORD!
	branches[27]->SetString("27. Make a sword!");
	branches[27]->SetChildren(branches[39], branches[39]);

	/*MAKE FORGE*/
	// [28] Workshop Waiting
	branches[28]->SetString("28. Is forge waiting?");
	branches[28]->SetChildren(branches[39], branches[29]);
	// [29] Forge Bar > 3
	branches[29]->SetString("29. Does forge have 3 bar?");
	branches[29]->SetChildren(branches[32], branches[36]);
	// [30] Forge Wood > 10 - No Bar
	branches[30]->SetString("30. Does forge have 10 wood?");
	branches[30]->SetChildren(branches[31], branches[35]);
	// [31] Have Builder - No Bar
	branches[31]->SetString("31. Is there a builder?");
	branches[31]->SetChildren(branches[39], branches[37]);
	// [32] Forge Wood > 10 - Has Bar
	branches[32]->SetString("32. Does forge have 10 wood?");
	branches[32]->SetChildren(branches[33], branches[35]);
	// [33] Have Builder - Has Bar
	branches[33]->SetString("33. Is there a builder?");
	branches[33]->SetChildren(branches[34], branches[37]);
	// [34] Builder Available
	branches[34]->SetString("34. Is builder available?");
	branches[34]->SetChildren(branches[38], branches[39]);
	// [35] GET WOOD
	branches[35]->SetString("35. Get wood for forge!");
	branches[35]->SetChildren(branches[31], branches[31]);
	// [36] ORDER BAR
	branches[36]->SetString("36. Order bar for forge!");
	branches[36]->SetChildren(branches[30], branches[30]);
	// [37] MAKE BUILDER!
	branches[37]->SetString("37. Make a builder!");
	branches[37]->SetChildren(branches[39], branches[39]);
	// [38] MAKE FORGE!
	branches[38]->SetString("38. Make a forge!");
	branches[38]->SetChildren(branches[39], branches[39]);

	/*MAKE BAR*/
	// [39] Have Smelt
	branches[39]->SetString("39. Is smelt built?");
	branches[39]->SetChildren(branches[40], branches[52]);
	// [40] Any Orders
	branches[40]->SetString("40. Does smelt have orders?");
	branches[40]->SetChildren(branches[41], branches[60]);
	// [41] Workshop Waiting
	branches[41]->SetString("41. Is smelt waiting?");
	branches[41]->SetChildren(branches[60], branches[42]);
	// [42] Smelt Ore > 2
	branches[42]->SetString("42. Does smelt have 2 ore?");
	branches[42]->SetChildren(branches[45], branches[48]);
	// [43] Smelt Coal > 3 - No Ore
	branches[43]->SetString("43. Does smelt have 3 coal?");
	branches[43]->SetChildren(branches[44], branches[49]);
	// [44] Have Smelter - No Ore
	branches[44]->SetString("44. Is there a smelter?");
	branches[44]->SetChildren(branches[60], branches[50]);
	// [45] Smelt Coal > 3 - Has Ore
	branches[45]->SetString("45. Does smelt have 3 coal?");
	branches[45]->SetChildren(branches[46], branches[49]);
	// [46] Have Smelter - Has Ore
	branches[46]->SetString("46. Is there a smelter?");
	branches[46]->SetChildren(branches[47], branches[40]);
	// [47] Smelt Available
	branches[47]->SetString("47. Is smelt available?");
	branches[47]->SetChildren(branches[51], branches[60]);
	// [48] GET ORE
	branches[48]->SetString("48. Get ore for smelt!");
	branches[48]->SetChildren(branches[43], branches[43]);
	// [49] ORDER COAL
	branches[49]->SetString("49. Order coal for smelt!");
	branches[49]->SetChildren(branches[44], branches[44]);
	// [50] MAKE SMELTER!
	branches[50]->SetString("50. Make a smelter!");
	branches[50]->SetChildren(branches[60], branches[60]);
	// [51] MAKE BAR!
	branches[51]->SetString("51. Make a bar!");
	branches[51]->SetChildren(branches[60], branches[60]);

	/*MAKE SMELT*/
	// [52] Workshop Waiting
	branches[52]->SetString("52. Is smelt waiting?");
	branches[52]->SetChildren(branches[60], branches[53]);
	// [53] Smelt Wood > 10
	branches[53]->SetString("53. Does smelt have 2 ore?");
	branches[53]->SetChildren(branches[55], branches[57]);
	// [54] Have Builder - No Wood
	branches[54]->SetString("54. Is there a builder?");
	branches[54]->SetChildren(branches[60], branches[58]);
	// [55] Have Builder - Has Wood
	branches[55]->SetString("55. Is there a builder?");
	branches[55]->SetChildren(branches[56], branches[58]);
	// [56] Builder Available
	branches[56]->SetString("56. Is builder available?");
	branches[56]->SetChildren(branches[59], branches[60]);
	// [57] GET WOOD
	branches[57]->SetString("57. Get wood for smelt!");
	branches[57]->SetChildren(branches[54], branches[54]);
	// [58] MAKE BUILDER!
	branches[58]->SetString("58. Make a builder!");
	branches[58]->SetChildren(branches[60], branches[60]);
	// [59] MAKE SMELT!
	branches[59]->SetString("59. Make a smelt!");
	branches[59]->SetChildren(branches[60], branches[60]);

	/*MAKE COAL*/
	// [60] Have Mill
	branches[60]->SetString("60. Is coal mill built?");
	branches[60]->SetChildren(branches[61], branches[70]);
	// [61] Any Orders
	branches[61]->SetString("61. Does coal mill have orders?");
	branches[61]->SetChildren(branches[62], branches[78]);
	// [62] Workshop Waiting
	branches[62]->SetString("62. Is coal mill waiting?");
	branches[62]->SetChildren(branches[78], branches[63]);
	// [63] Mill Wood > 2
	branches[63]->SetString("63. Does coal mill have 2 wood?");
	branches[63]->SetChildren(branches[65], branches[67]);
	// [64] Have Miner - No Wood
	branches[64]->SetString("64. Is there a miner?");
	branches[64]->SetChildren(branches[78], branches[68]);
	// [65] Have Miner - Has Wood
	branches[65]->SetString("65. Is there a miner?");
	branches[65]->SetChildren(branches[66], branches[68]);
	// [66] Mill Available
	branches[66]->SetString("66. Is coal mill available?");
	branches[66]->SetChildren(branches[69], branches[78]);
	// [67] GET WOOD
	branches[67]->SetString("67. Get wood for coal mill!");
	branches[67]->SetChildren(branches[64], branches[64]);
	// [68] MAKE MINER!
	branches[68]->SetString("68. Make a miner!");
	branches[68]->SetChildren(branches[78], branches[78]);
	// [69] MAKE COAL!
	branches[69]->SetString("69. Make a coal!");
	branches[69]->SetChildren(branches[78], branches[78]);

	/*MAKE MILL*/
	// [70] Workshop Waiting
	branches[70]->SetString("70. Is coal mill waiting?");
	branches[70]->SetChildren(branches[78], branches[71]);
	// [71] Mill Wood > 10
	branches[71]->SetString("71. Does coal mill have 10 wood?");
	branches[71]->SetChildren(branches[73], branches[75]);
	// [72] Have Builder - No Wood
	branches[72]->SetString("72. Is there a builder?");
	branches[72]->SetChildren(branches[78], branches[76]);
	// [73] Have Builder - Has Wood
	branches[73]->SetString("73. Is there a builder?");
	branches[73]->SetChildren(branches[74], branches[76]);
	// [74] Builder Available
	branches[74]->SetString("74. Is builder available?");
	branches[74]->SetChildren(branches[77], branches[78]);
	// [75] GET WOOD
	branches[75]->SetString("75. Get wood for coal mill!");
	branches[75]->SetChildren(branches[72], branches[72]);
	// [76] MAKE BUILDER!
	branches[76]->SetString("76. Make a builder!");
	branches[76]->SetChildren(branches[78], branches[78]);
	// [77] MAKE MILL!
	branches[77]->SetString("76. Make a coal mill!");
	branches[77]->SetChildren(branches[78], branches[78]);
}

DecisionTree::DecisionTree(Map* newMap, StaffManager* newStaff)
{
	map = newMap;
	staff = newStaff;

	MakeTree();
}

void DecisionTree::WalkTree()
{
	branches[0]->WalkTree(*map, *staff);
}
