#pragma once

#include <vector>
#include "branch.h"
#include "map.h"
#include "StaffManager.h"

class DecisionTree
{
private:
	Map* map;
	StaffManager* staff;
	vector<Branch*> branches;
	void MakeTree();

public:
	DecisionTree(Map* newMap, StaffManager* newStaff);
	~DecisionTree() {};

	void WalkTree();
};
