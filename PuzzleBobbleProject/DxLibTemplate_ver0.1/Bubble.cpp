#include "Bubble.h"

Bubble::Bubble(int _col, Float2 _pos, float _radius) : Task(TaskManager::getInstance()->generateId()), rCir(PRIORITY_SPRITE, _pos, _radius), position(_pos)
{
	switch (_col)
	{
	case COLOR::COL_RED:
		rCir.setColor(255, 0, 0);
		break;
	case COLOR::COL_BLUE:
		rCir.setColor(0, 0, 255);
		break;
	case COLOR::COL_YELLOW:
		rCir.setColor(255, 255, 0);
		break;
	case COLOR::COL_GREEN:
		rCir.setColor(0, 255, 0);
		break;
	case COLOR::COL_ORANGE:
		rCir.setColor(255, 128, 0);
		break;
	case COLOR::COL_PURPLE:
		rCir.setColor(255, 0, 255);
		break;
	}
	color = _col;
	canDestroy = false;
	isChecked = false;
	RenderableManager::getInstance()->addObject(&rCir);
	state = STATE::RELOAD;
}

Bubble::~Bubble()
{

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
	CollisionManager::getInstance()->removeObject(&cBubble);
	RenderableManager::getInstance()->removeObject(&rCir);

}

int Bubble::getColor()
{
	return color;
}

void Bubble::setState(int newState)
{
	if (STATE::NUM <= state) return;

	state = newState;
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
