#include "objects.h"

void Tree::Draw()
{
	DrawCircle(position.x, position.y, 1 * resMult, Mgreen);
}


void Ore::Draw()
{
	DrawCircle(position.x, position.y, 1 * resMult, Mblack);
}