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
	CCircle* c = new CCircle;
	cBubble.setShape(c);

	ShapeSetParam param(ShapeSetParam::ParamType::PT_CIRCLE);
	param.param.paramCircle.point = position;
	param.param.paramCircle.r = BUBBLE_RADIUS;

	cBubble.getShape()->paramUpdate(&param);

	RenderableManager::getInstance()->addObject(&rCir);
	state = STATE::STAY;
}

Bubble::~Bubble()
{

}

void Bubble::Update()
{
	switch (state)
	{
	case STATE::RELOAD:
		if (position.x <= BALLISTA_BASE_X)
		{
			Vector2D vectorX(5.0f, 0.0f);
			move(vectorX, 5.0f);
		}
		else
		{
			position.x = BALLISTA_BASE_X;
			setState(STATE::READY);
		}
		break;
	case STATE::STAY:
		break;

	case STATE::READY:
		break;

	case STATE::SHOOT:
		move(vec, BUBBLE_MOVE_SPEED);
		break;

	case STATE::FIXED:
		break;

	case STATE::VANISH:
		break;
	}


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

int Bubble::getState()
{
	return state;
}

void Bubble::setVector(Vector2D _vec)
{
	vec = _vec;
}

bool Bubble::hit()
{
	auto colIdx = cBubble.getInfoIdx();
	for (auto& idx : colIdx)
	{
		if (idx == INFO_INDEX_DEFAULT) continue;
		std::weak_ptr<CollisionInfo> info = CollisionManager::getInstance()->getColInfoFromIdx(idx);
		if (!info.lock()) continue;
		if (info.lock()->getEnter())
		{

			if (state == STATE::SHOOT)
			{
				auto targetBubble = info.lock()->getTarget(&cBubble);
				if (targetBubble->getMark() == CollisionObject::BUBBLE)

				{
					return true;
				}

			}
		}

	}
	


	return false;
}


Float2 Bubble::getPos()
{
	return position;
}

void Bubble::move(Vector2D _vec, float speed)
{
	position += _vec * speed;
	rCir.set(position, BUBBLE_RADIUS);

	ShapeSetParam param(ShapeSetParam::ParamType::PT_CIRCLE);
	param.param.paramCircle.point = position;
	param.param.paramCircle.r = BUBBLE_RADIUS;

	cBubble.getShape()->paramUpdate(&param);
	

		auto colIdx = cBubble.getInfoIdx();
		for (auto& idx : colIdx)
		{
			if (idx == INFO_INDEX_DEFAULT) continue;
			std::weak_ptr<CollisionInfo> info = CollisionManager::getInstance()->getColInfoFromIdx(idx);
			if (!info.lock()) continue;

			if (info.lock()->getEnter())
			{
				if (info.lock()->getTarget(&cBubble)->getMark() == CollisionObject::WALL && state == STATE::SHOOT)
				{
					vec.x *= -1.0f;
				}
			}

		}
}

void Bubble::setIsChecked(bool check)
{
	isChecked = check;
}

void Bubble::setCanDestroy(bool _canDestroy)
{
	canDestroy = _canDestroy;
}

void Bubble::setPos(Float2 _pos)
{
	position = _pos;
	rCir.set(position, BUBBLE_RADIUS);

	ShapeSetParam param(ShapeSetParam::ParamType::PT_CIRCLE);
	param.param.paramCircle.point = position;
	param.param.paramCircle.r = BUBBLE_RADIUS;

	cBubble.getShape()->paramUpdate(&param);
}

bool Bubble::getIsChecked()
{
	return isChecked;
}

bool Bubble::getCanDestroy()
{
	return canDestroy;
}
