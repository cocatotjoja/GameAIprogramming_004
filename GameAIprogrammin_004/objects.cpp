#include "objects.h"
#include "map.h"
#include "StaffManager.h"


void Tree::Draw()
{
	if (cut == false)
	{
		DrawCircle(position.x, position.y, 1 * resMult, Mlightgreen);
	}
}

void Ore::Draw()
{
	if (cut == false)
	{
		DrawCircle(position.x, position.y, 1 * resMult, Mdarkgrey);
	}
}

void Workshop::Update()
{
	switch (state)
	{
	case WAITING:
		Waiting();
		break;
	case RUNNING:
		Running();
		break;
	case AVAILABLE:
		break;
	default:
		break;
	}
}

void Workshop::Draw()
{
	if (built)
	{
		Vector2 size = { 10.0f * resMult, 10.0f * resMult };
		Rectangle boundary = { position.x, position.y, size.x, size.y };
		switch (type)
		{
		case COAL_MILL:
			DrawRectangleRec(boundary, Mblue);
			break;
		case SMELT:
			DrawRectangleRec(boundary, Mgreen);
			break;
		case FORGE:
			DrawRectangleRec(boundary, Myellow);
			break;
		case TRAINING_CAMP:
			DrawRectangleRec(boundary, Mred);
			break;
		default:
			break;
		}
	}
}

void Workshop::AddMaterial(Product product)
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
	case SOLDIER:
		staff->MakeSoldier();
		break;
	default:
		break;
	}
}

void Workshop::RemoveMaterial(Product product)
{
	switch (product)
	{
	case WOOD:
		wood--;
		break;
	case ORE:
		ore--;
		break;
	case COAL:
		coal--;
		break;
	case BAR:
		bar--;
		break;
	case SWORD:
		sword--;
		break;
	default:
		break;
	}
}

void Workshop::UseMaterials()
{
	switch (type)
	{
	case COAL_MILL:
		if (built)
		{
			wood -= 2;
		}
		else
		{
			wood -= 10;
		}
		break;

	case SMELT:
		if (built)
		{
			ore -= 2;
			coal -= 3;
		}
		else
		{
			wood -= 10;
		}
		break;

	case FORGE:
		if (built)
		{
			bar -= 1;
			coal -= 2;
		}
		else
		{
			ore -= 3;
			wood -= 10;
		}
		break;

	case TRAINING_CAMP:
		if (built)
		{
			sword >= 1;
		}
		else
		{
			wood -= 10;
		}
		break;

	default:
		break;
	}
}

int Workshop::CheckInventory(Product product)
{
	switch (product)
	{
	case WOOD:
		return wood;
	case ORE:
		return ore;
	case COAL:
		return coal;
	case BAR:
		return bar;
	case SWORD:
		return sword;
	default:
		return -1;
	}
}

void Workshop::Running()
{
	if (built)
	{
		if (timer > 0.0f)
		{
			timer -= GetFrameTime();
		}
		else
		{
			AddMaterial(produce);
			orders--;
			timer = 0.0;
			state = AVAILABLE;
		}
	}
	else
	{
		if (timer > 0.0f)
		{
			timer -= GetFrameTime();
		}
		else
		{
			built = true;
			timer = 0;
			state = AVAILABLE;
		}
	}
}

void Workshop::Waiting()
{
	if (built)
	{
		switch (type)
		{
		case COAL_MILL:
			if (wood >= 2)
			{
				timer = 30.0;
				state = AVAILABLE;
			}
			break;
		case SMELT:
			if (ore >= 2 && coal >= 3)
			{
				timer = 30.0;
				state = AVAILABLE;
			}
			break;
		case FORGE:
			if (bar >= 1 && coal >= 2)
			{
				timer = 60.0;
				state = AVAILABLE;
			}
			break;
		case TRAINING_CAMP:
			if (sword >= 1)
			{
				timer = 60.0;
				state = AVAILABLE;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (type)
		{
		case COAL_MILL:
			if (wood >= 10)
			{
				timer = 60.0;
				state = AVAILABLE;
			}
			break;
		case SMELT:
			if (wood >= 10)
			{
				timer = 120.0;
				state = AVAILABLE;
			}
			break;
		case FORGE:
			if (ore >= 3 && wood >= 10)
			{
				timer = 180.0;
				state = AVAILABLE;
			}
			break;
		case TRAINING_CAMP:
			if (wood >= 10)
			{
				timer = 120.0;
				state = AVAILABLE;
			}
			break;
		default:
			break;
		}
	}
}
