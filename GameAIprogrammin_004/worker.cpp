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
	default:
		break;
	}
	// Update position
	position += velocity * GetFrameTime();
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
	// Check if it has the product
	if (HaveProduct())
	{
		//Then deliver where needed
		switch (workshop)
		{
		case COAL_MILL:
			// GET PATH TO COAL MILL
			break;
		case SMELT:
			// GET PATH TO SMELT
			break;
		case FORGE:
			// GET PATH TO FORGE
			break;
		case TRAINING_CAMP:
			// GET PATH TO TRAINING CAMP
			break;
		default:
			break;
		}
		state = TRANSPORT;
	}
	else
	{
		// If not go to the correct workshop
		switch (product)
		{
		case WOOD:
			// GET PATH TO NEAREST TREE
			break;
		case ORE:
			// GET PATH TO NEAREST ORE
			break;
		case COAL:
			// GET PATH TO COAL MILL
			break;
		case BAR:
			// GET PATH TO SMELT
			break;
		case SWORD:
			// GET PATH TO FORGE
			break;
		default:
			break;
		}
		state = HARVEST;

	}
}

void Worker::Harvest()
{
	if (path.empty())
	{
		velocity = { 0,0 };
		if (!harvesting)
		{
			harvesting = true;
			if (product == WOOD)
			{
				timer = 30;
			}
		}
		if (timer > 0.0)
		{
			timer -= GetFrameTime();
		}
		else
		{
			switch (product)
			{
			case WOOD:
				wood++;
				break;
			case ORE:
				ore++;
				break;
			case COAL:
				coal++;
				break;
			case BAR:
				bar++;
				break;
			case SWORD:
				sword++;
				break;
			default:
				break;
			}
			harvesting = false;
			state = TRANSPORT;
		}
	}
	else
	{
		FollowPath();
	}
}

void Worker::Transport()
{
	if (path.empty() < 1)
	{
		velocity = { 0,0 };
		switch (workshop)
		{
		case COAL_MILL:
			// GET PATH TO COAL MILL
			break;
		case SMELT:
			// GET PATH TO SMELT
			break;
		case FORGE:
			// GET PATH TO FORGE
			break;
		case TRAINING_CAMP:
			// GET PATH TO TRAINING CAMP
			break;
		default:
			break;
		}
		state = IDLE;
	}
	else
	{
		FollowPath();
	}
}

Scout::Scout(Vector2 quad, Vector2 newPos, Map* newMap)
{
	quadrant = quad;
	position = newPos;
	map = newMap;
	timer = 3.0f;		// Should be 60.0f
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
		// TODO: Increase workshop product count
		state = IDLE;
	}
}
