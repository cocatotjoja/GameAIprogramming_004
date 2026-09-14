#include "node.h"

Node::Node()
{
	ID = { 0,0 };
	position = { 0,0 };
	type = 'T';
}

Node::Node(int x, int y, char Type)
{
	ID = { (float)x, (float)y };
	position = ID * 10 * resMult;
	type = Type;

	if (type == 'T')
	{
		ground = MdarkGreen;
	}
	else if (type == 'V')
	{
		blocked = true;
		ground = Mlightblue;
	}
	else if (type == 'G')
	{
		ground = MdarkBrown;
	}
	else if (type == 'B')
	{
		blocked = true;
		ground = Mburgundy;
	}
}

bool Node::IsBlocked()
{
	if (type == 'B' || type == 'V' || blocked)
	{
		return true;
	}
	return false;
}

bool Node::BlockedORFogged()
{
	if (type == 'B' || type == 'V' || blocked || fog == true)
	{
		return true;
	}
	return false;
}

void Node::SetValues(float parentValue, Vector2 goal)
{
	Vector2 goalID = goal / (10 * resMult);
	valueSofar = parentValue;
	valueLeft = abs(ID.x - goalID.x) + abs(ID.y - goalID.y);
	valueTotal = valueSofar + valueLeft;
}

void Node::ResetNode()
{
	valueSofar = NULL;
	valueLeft = NULL;
	valueTotal = NULL;
	parent = ID;
	state = 1;
}
void Node::Draw()
{
	Rectangle boundary = { position.x, position.y, size.x, size.y };
	DrawRectangleRec(boundary, ground);
}

void Node::DrawFog()
{
	if (fog)
	{
		Rectangle boundary = { position.x, position.y, size.x, size.y };
		DrawRectangleRec(boundary, Mlightgrey);
	}
}
