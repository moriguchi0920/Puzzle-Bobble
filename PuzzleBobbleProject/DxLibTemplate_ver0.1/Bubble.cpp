#include "Bubble.h"

Bubble::Bubble(int _col, Float2 _pos, float _radius) : Task(TaskManager::getInstance()->generateId()), rCir(PRIORITY_SPRITE, _pos, _radius), position(_pos)
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
	RenderableManager::getInstance()->addObject(&rCir);
}

void Bubble::Update()
{
}

bool Bubble::Destroy()
{
	return false;
}

void Bubble::activateProc()
{
}

void Bubble::deactivateProc()
{
}

DebugColor& Bubble::getColor()
{
	return col;
}

void Bubble::move(Vector2D vec, float speed)
{
	position += vec * speed;

}

void Bubble::setIsChecked(bool check)
{
	isChecked = check;
}

void Bubble::setCanDestroy(bool _canDestroy)
{
	canDestroy = _canDestroy;
}

bool Bubble::getIsChecked()
{
	return isChecked;
}

bool Bubble::getCanDestroy()
{
	return canDestroy;
}
