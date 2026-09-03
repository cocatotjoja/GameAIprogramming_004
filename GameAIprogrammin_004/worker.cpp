#include "worker.h"

void Worker::Update()
{
	// Update Velocity
	switch (state)
	{
	case IDLE:
		velocity = { 0,0 };
		break;
	case HARVEST:
		Harvest();
		break;
	case TRANSPORT:
		Transport();
		break;
	case SEARCH:
		Search();
		break;
	default:
		break;
	}


	if (Vector2Length(velocity) > maxSpeed)
	{
		velocity = Vector2Normalize(velocity) * maxSpeed;
	}
	// Update position
	position += velocity;
}

void Worker::Draw()
{
	Rectangle boundary = { position.x, position.y, 4*resMult, 4*resMult };
	DrawRectangleRec(boundary, Mred);
}

Vector2 Worker::Seek(Vector2 targetPos)
{
	// Calculate velocity
	Vector2 result = targetPos - position;

	//give max acceleration
	result = Vector2Normalize(result) * maxAcceleration;


	return result;
}

void Worker::FollowPath()
{
	if (Vector2Distance(position, path.top()) < (4))
	{
		path.pop();
	}
	if (path.empty())
	{
		return;
	}
	//velocity += Seek(path.top()) * GetFrameTime();
	velocity += Seek(path.top());
}

bool Worker::HaveProduct()
{
	switch (product)
	{
	case WOOD:
		return wood;
		break;
	case ORE:
		return ore;
		break;
	case COAL:
		return coal;
		break;
	case BAR:
		return bar;
		break;
	case SWORD:
		return sword;
		break;
	default:
		return false;
		break;
	}
}

bool Worker::IsFree()
{
	if (state == IDLE)
	{
		return true;
	}
	return false;
}

void Worker::GetProduct(Product newProduct, WorkshopType newWorkshopType)
{
	product = newProduct;
	workshop = newWorkshopType;
	state = SEARCH;
}

void Worker::Harvest()
{
	if (path.empty())
	{
		switch (product)
		{
		case WOOD:
			if (timer > 0.0)
			{
				timer -= GetFrameTime();
			}
			else
			{
				wood++;
				map->trees[materialID].cut = true;
				state = TRANSPORT;
			}
			break;

		case ORE:
			ore++;
			map->ironOre[materialID].cut = true;
			state = TRANSPORT;
			break;

		case COAL:
			// Check for product
			if (map->GetWorkshop(COAL_MILL)->CheckInventory(COAL));
			{
				map->GetWorkshop(COAL_MILL)->RemoveMaterial(COAL);
				coal++;
				state = TRANSPORT;

			}
			break;

		case BAR:
			// Check for product
			if (map->GetWorkshop(SMELT)->CheckInventory(BAR));
			{
				map->GetWorkshop(SMELT)->RemoveMaterial(BAR);
				bar++;
				state = TRANSPORT;

			}
			break;

		case SWORD:
			// Check for product
			if (map->GetWorkshop(FORGE)->CheckInventory(SWORD));
			{
				map->GetWorkshop(FORGE)->RemoveMaterial(SWORD);
				sword++;
				state = TRANSPORT;

			}
			break;

		default:
			break;
		}
		harvesting = false;
		state = TRANSPORT;
	}
	else
	{
		FollowPath();
	}
}

void Worker::Transport()
{
	// TODO:
}

void Worker::Search()
{
	Vector2 goalNode;
	Vector2 startNode = GetNearestNode(position);
	int ID;
	switch (product)
	{
	case WOOD:
		// GET TREE
		ID = map->GetTree();
		// GET PATH TO TREE
		goalNode = GetNearestNode(map->trees[ID].position);
		map->GetPath(startNode, goalNode, path);

		// TODO: Handle if no tree is available

		materialID = ID;
		map->trees[materialID].booked = true;
		timer = 30.0;
		state = HARVEST;
		break;

	case ORE:
		// GET ORE
		ID = map->GetOre();
		// GET PATH TO ORE
		goalNode = GetNearestNode(map->ironOre[ID].position);
		map->GetPath(startNode, goalNode, path);

		// TODO: Handle if no ore is available

		materialID = ID;
		map->ironOre[materialID].booked = true;
		state = HARVEST;
		break;

	case COAL:
		// GET PATH TO COAL MILL
		goalNode = GetNearestNode(map->GetWorkshop(COAL_MILL)->GetPosition());
		map->GetPath(startNode, goalNode, path);

		state = HARVEST;
		break;

	case BAR:
		// GET PATH TO SMELT
		goalNode = GetNearestNode(map->GetWorkshop(SMELT)->GetPosition());
		map->GetPath(startNode, goalNode, path);

		state = HARVEST;
		break;

	case SWORD:
		// GET PATH TO FORGE
		goalNode = GetNearestNode(map->GetWorkshop(FORGE)->GetPosition());
		map->GetPath(startNode, goalNode, path);

		state = HARVEST;
		break;

	default:
		break;
	}
}

Scout::Scout(Vector2 newPos, Map* newMap)
{
	position = newPos;
	map = newMap;
	timer = 60.0f;
}

void Scout::Update()
{
	if (timer > 0.0)
	{
		timer -= GetFrameTime();
		return;
		if (timer < 0.0)
		{
			state = SCOUT;
		}
	}
	switch (state)
	{
	case IDLE:
		velocity = { 0, 0 };
		break;
	case SCOUT:
		Scouting();
		break;
	default:
		break;
	}


	if (Vector2Length(velocity) > maxSpeed)
	{
		velocity = Vector2Normalize(velocity) * maxSpeed;
	}
	// Update position
	position += velocity;
}

void Scout::Scouting()
{
	Vector2 currentNode = GetNearestNode(position);

	// Clear nearby fog
	map->RemoveFog(currentNode);
	map->RemoveFog(currentNode + Vector2{  1,  1 });
	map->RemoveFog(currentNode + Vector2{ -1, -1 });	
	map->RemoveFog(currentNode + Vector2{  0, -1 });
	map->RemoveFog(currentNode + Vector2{  0,  1 });
	map->RemoveFog(currentNode + Vector2{  -1, 0 });
	map->RemoveFog(currentNode + Vector2{   1, 0 });
	map->RemoveFog(currentNode + Vector2{   1, -1 });
	map->RemoveFog(currentNode + Vector2{  -1,  1 });
	
	while (path.empty())
	{
		Vector2 nextFog = map->GetFogPosRand();
		if (nextFog == Vector2{ -1, -1 })
		{
			state = IDLE;
			return;
		}
		else
		{
			map->GetPath(currentNode, nextFog, path);
		}
	}

	FollowPath();
}

Soldier::Soldier(float time, Vector2 newPos, Map* newMap)
{
	timer = time;
	position = newPos;
	map = newMap;
}

void Soldier::Update()
{
	switch (state)
	{
	case IDLE:
		velocity = { 0, 0 };
		break;
	default:
		break;
	}
	// Update position
	position += velocity * GetFrameTime();
}

void Crafter::GetCrafting()
{
	state = CRAFTING;
	timer = craftingTime;
}

void Crafter::Update()
{
	switch (state)
	{
	case IDLE:
		velocity = { 0, 0 };
		break;
	case CRAFTING:
		Crafting();
		break;
	default:
		break;
	}
	// Update position
	position += velocity * GetFrameTime();
}

void Crafter::Crafting()
{
	if (timer > 0)
	{
		timer -= GetFrameTime();
	}
	else
	{
		state = IDLE;
	}
}
