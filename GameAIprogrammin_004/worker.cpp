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
	Rectangle boundary = { position.x, position.y, 1*resMult, 1*resMult };
	DrawRectangleRec(boundary, Mwhite);
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
	velocity += Seek(path.top()) * GetFrameTime();
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
	if (path.size() < 1)
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
		if (timer > 0)
		{
			timer--;
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
	if (path.size() < 1)
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

void Scout::Update()
{
	switch (state)
	{
	case IDLE:
		velocity = { 0, 0 };
		break;
	case SCOUT:
		// TODO
		break;
	default:
		break;
	}
	// Update position
	position += velocity * GetFrameTime();
}

void Scout::Scouting()
{
	// TODO
	if (target == Vector2{ (float)-1, (float)-1 })
	{
		// TODO: Find new target
	}
	else
	{
		// TODO: Get path to new target
	}
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
void Crafter::GetCrafting(int time)
{
	state = CRAFTING;
	timer = time;
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
		timer--;
	}
	else
	{
		// TODO: Increase workshop product count
		state = IDLE;
	}
}
