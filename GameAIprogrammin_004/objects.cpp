#include "objects.h"

void Tree::Draw()
{
	DrawCircle(position.x, position.y, 1 * resMult, Mgreen);
}


void Ore::Draw()
{
	DrawCircle(position.x, position.y, 1 * resMult, Mblack);
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
