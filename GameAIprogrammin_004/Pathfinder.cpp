#include "Pathfinder.h"
#include <cstdlib>
using namespace std;

//Return 0, if shouldn'd add, returns 1 if unchecked, returns 2 if opened, returns 3 if closed
int Pathfinder::ShouldAdd(Node(&map1)[100][100], int x, int y, int corner, int width, int height)
{
	//Check if within map
	if (x < width - 1 && x > 0 && y < height - 1 && y > 0)
	{
		// Check if blocked
		if (map1[x][y].IsBlocked())
		{
			return 0;
		}

		//Check diagonal
		switch (corner)
		{
		case 1:
			if (map1[x + 1][y].IsBlocked() || map1[x][y - 1].IsBlocked())
			{
				return 0;
			}
			break;
		case 2:
			if (map1[x - 1][y].IsBlocked() || map1[x][y - 1].IsBlocked())
			{
				return 0;
			}
			break;
		case 3:
			if (map1[x + 1][y].IsBlocked() || map1[x][y + 1].IsBlocked())
			{
				return 0;
			}
			break;
		case 4:
			if (map1[x - 1][y].IsBlocked() || map1[x][y + 1].IsBlocked())
			{
				return 0;
			}
			break;
		default:
			break;
		}

		// Check state, Unchecked = 1, Opened = 2, Closed = 3
		switch (map1[x][y].GetState())
		{
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;
		default:
			break;
		}
	}
	else
	{
		return 0;
	}
}

void Pathfinder::AddNode(Node(&map1)[100][100], Vector2 parentID, int parentXplus, int parentYplus, float addValue, int corner, float parentValue, int width, int height, Vector2 goal)
{
	switch (ShouldAdd(map1, parentXplus, parentYplus, corner, width, height))
	{
	case 1:
		// Update Value, Parent, and state
		map1[parentXplus][parentYplus].SetValues(parentValue + addValue, goal);
		map1[parentXplus][parentYplus].SetParent(parentID);
		map1[parentXplus][parentYplus].SetState(2);

		// Add to open list
		opened.push_back(&(map1[parentXplus][parentYplus]));
		break;
	case 2:
		// Compare and update value and parent if needed
		if (map1[parentXplus][parentYplus].GetValueSofar() > parentValue + addValue)
		{
			map1[parentXplus][parentYplus].SetValues(parentValue + addValue, goal);
			map1[parentXplus][parentYplus].SetParent(parentID);
		}
		break;
	case 3:
		// If new value is smaller than existing
		if (map1[parentXplus][parentYplus].GetValueSofar() > parentValue + addValue)
		{
			// Update Value, Parent, and state
			map1[parentXplus][parentYplus].SetValues(parentValue + addValue, goal);
			map1[parentXplus][parentYplus].SetParent(parentID);
			map1[parentXplus][parentYplus].SetState(2);

			// Add to open list
			opened.push_back(&(map1[parentXplus][parentYplus]));

			// Remove from closed list
			for (int i = 0; i < closed.size(); i++)
			{
				if (map1[parentXplus][parentYplus].GetPosition() == closed[i]->GetPosition())
				{
					closed.at(i) = closed.back();
					closed.pop_back();
				}
			}
		}
		break;
	default:
		break;
	}
}


void Pathfinder::FindPath(Node(&map1)[100][100], int width, int height, Vector2 start, Vector2 goal, stack<Vector2> &returnPath)
{
	if (found)
	{
		return;
	}

	if (opened.empty())
	{
		int x = start.x / 20;
		int y = start.y / 20;
		opened.push_back(&(map1[1][height - 2]));
		map1[x][y].SetValues(0, goal);
		map1[x][y].SetState(2);
		map1[x][y].SetParent(map1[x][y].GetID());
	}
	

	while (!found)
	{
		// Loop through opened nodes and find the smallest one
		int smallestID = 0;
		int smallestValue = opened[0]->GetValueTotal();
		for (int i = 0; i < opened.size(); i++)
		{
			if (opened[i]->GetValueTotal() < smallestValue)
			{
				smallestID = i;
				smallestValue = opened[i]->GetValueTotal();
			}
		}


		if (opened[smallestID]->GetPosition() == goal)
		{

			Vector2 currentID = opened[smallestID]->GetID();
			while (currentID != map1[(int)currentID.x][(int)currentID.y].GetParent())
			{
				//map1[(int)currentID.x][(int)currentID.y].SetState(4);
				returnPath.push(currentID * 10 * resMult);
				currentID = map1[(int)currentID.x][(int)currentID.y].GetParent();
			}
			found = true;
		}
		else
		{
			// Save parent node ID and Value for adding nodes
			Vector2 parentID = opened[smallestID]->GetID();
			float parentValue = opened[smallestID]->GetValueSofar();


			// ADD Adjacent nodes
			//map1[(int)parentID.x + 1][(int)parentID.y];
			AddNode(map1, parentID, (int)parentID.x + 1, (int)parentID.y, 1.0f, 0, parentValue, width, height, goal);
			//map1[(int)parentID.x - 1][(int)parentID.y];
			AddNode(map1, parentID, (int)parentID.x - 1, (int)parentID.y, 1.0f, 0, parentValue, width, height, goal);
			//map1[(int)parentID.x][(int)parentID.y + 1];
			AddNode(map1, parentID, (int)parentID.x, (int)parentID.y + 1, 1.0f, 0, parentValue, width, height, goal);
			//map1[(int)parentID.x][(int)parentID.y - 1];
			AddNode(map1, parentID, (int)parentID.x, (int)parentID.y - 1, 1.0f, 0, parentValue, width, height, goal);

			// ADD Diagonal Nodes
			//map1[(int)parentID.x - 1][(int)parentID.y + 1];
			AddNode(map1, parentID, (int)parentID.x - 1, (int)parentID.y + 1, 1.4f, 1, parentValue, width, height, goal);
			//map1[(int)parentID.x + 1][(int)parentID.y + 1];
			AddNode(map1, parentID, (int)parentID.x + 1, (int)parentID.y + 1, 1.4f, 2, parentValue, width, height, goal);
			//map1[(int)parentID.x - 1][(int)parentID.y - 1];
			AddNode(map1, parentID, (int)parentID.x - 1, (int)parentID.y - 1, 1.4f, 3, parentValue, width, height, goal);
			//map1[(int)parentID.x + 1][(int)parentID.y - 1];
			AddNode(map1, parentID, (int)parentID.x + 1, (int)parentID.y - 1, 1.4f, 4, parentValue, width, height, goal);


			// Add currently looked at node to closed list and update its state
			//opened[smallestID]->SetState(3);
			map1[(int)parentID.x][(int)parentID.y].SetState(3);
			closed.push_back(&(map1[(int)parentID.x][(int)parentID.y]));

			// Remove currently looked at node from opened list
			opened.at(smallestID) = opened.back();
			opened.pop_back();
		}

	}

	// Reset all nodes
	for (size_t x = 0; x < 100; x++)
	{
		for (size_t y = 0; y < 100; y++)
		{
			map1[x][y].ResetNode();
		}
	}
}
