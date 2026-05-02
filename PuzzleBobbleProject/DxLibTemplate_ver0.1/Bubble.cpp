#include "Bubble.h"

Bubble::Bubble(int _col, Float2 _pos, float _radius) : Task(TaskManager::getInstance()->generateId()), Rcir(PRIORITY_SPRITE, _pos, _radius)
{
	switch (_col)
	{
	case COLOR::COL_RED:
		col.set(255, 0, 0);
		break;
	case COLOR::COL_BLUE:
		col.set(0, 0, 255);
		break;
	case COLOR::COL_YELLOW:
		col.set(255, 255, 0);
		break;
	case COLOR::COL_GREEN:
		col.set(0, 255, 0);
		break;
	case COLOR::COL_ORANGE:
		col.set(255, 128, 0);
		break;
	case COLOR::COL_PURPLE:
		col.set(255, 0, 255);
		break;
	}
	canDestroy = false;
	isChecked = false;
}

void Bubble::Update()
{
}

bool Bubble::Destroy()
{
	return false;
}

DebugColor& Bubble::getColor()
{
	return col;
}
