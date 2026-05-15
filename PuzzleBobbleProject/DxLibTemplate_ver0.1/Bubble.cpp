#include "Bubble.h"
#include"AnimationRepository.h"

Bubble::Bubble(int _col, Float2 _pos, float _radius, bool isShoot) : Task(TaskManager::getInstance()->generateId()), rBubble(PRIORITY_SPRITE, AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_BLUE)), position(_pos)
{

	switch (_col)
	{
	case COLOR::COL_RED:
		rBubble.getAP().setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_RED));
		//rCir.setColor(255, 0, 0);
		break;
	case COLOR::COL_BLUE:
		rBubble.getAP().setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_BLUE));
		//rCir.setColor(0, 0, 255);
		break;
	case COLOR::COL_YELLOW:
		rBubble.getAP().setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_YELLOW));
		//rCir.setColor(255, 255, 0);
		break;
	case COLOR::COL_GREEN:
		rBubble.getAP().setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_GREEN));
		//rCir.setColor(0, 255, 0);
		break;
	case COLOR::COL_ORANGE:
		rBubble.getAP().setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_ORANGE));
		//rCir.setColor(255, 128, 0);
		break;
	case COLOR::COL_PURPLE:
		rBubble.getAP().setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_PURPLE));
		//rCir.setColor(255, 0, 255);
		break;
	case COLOR::COL_GRAY:
		rBubble.getAP().setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_GRAY));
		//rCir.setColor(128, 128, 128);
		break;
	case COLOR::COL_WHITE:
		rBubble.getAP().setAds(AnimationRepository::getInstance()->getAds(AnimationRepository::AOT_BUBBLE_WHITE));
		//rCir.setColor(255, 255, 255);
		break;
	}
	color = _col;
	canDestroy = false;
	isChecked = false;

	if (isShoot)
	{
		cBubble = std::make_unique<CShootBubble>();
	}
	else
	{
		cBubble = std::make_unique<CStageBubble>();
	}


	CCircle* c = new CCircle;
	cBubble->setShape(c);


	ShapeSetParam param(ShapeSetParam::ParamType::PT_CIRCLE);
	param.param.paramCircle.point = position;
	param.param.paramCircle.r = BUBBLE_RADIUS;

	cBubble->getShape()->paramUpdate(&param);

	rBubble.setBase(position);
	RenderableManager::getInstance()->addObject(&rBubble);
	state = STATE::STAY;

	gravity = 0.0f;
}

Bubble::~Bubble()
{

}

void Bubble::Update()
{
	rBubble.getAP().update();
	switch (state)
	{
	case STATE::RELOAD:
		if (position.x <= BALLISTA_BASE_X)
		{
			Vector2D vectorX(5.0f, -1.8f);
			move(vectorX, 5.0f);
		}
		else
		{
			Float2 pos(BALLISTA_BASE_X + 4, position.y);
			setPos(pos);
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

	case STATE::FALL:
		cBubble->setIsCollide(false);
		fall();
		break;
	}


}

bool Bubble::Destroy()
{
	return false;
}

void Bubble::activateProc()
{
	taskState = Task::ACTIVE;
}

void Bubble::deactivateProc()
{
	CollisionManager::getInstance()->removeObject(cBubble.get());
	RenderableManager::getInstance()->removeObject(&rBubble);
	taskState = Task::INACTIVE;
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
	auto colId = cBubble->getInfoId();
	for (auto& id : colId)
	{
		if (id == INFO_ID_DEFAULT) continue;
		std::weak_ptr<CollisionInfo> info = CollisionManager::getInstance()->getColInfoFromId(id);
		if (!info.lock()) continue;
		if (info.lock()->getEnter())
		{

			if (state == STATE::SHOOT)
			{
				auto targetBubble = info.lock()->getTarget(cBubble.get());
				if (targetBubble->getMark() == CollisionObject::STAGEBUBBLE)

				{
					return true;
				}

			}
		}

	}
	


	return false;
}

void Bubble::setStage()
{
	CollisionManager::getInstance()->removeObject(cBubble.get());
	cBubble.reset(nullptr);
	cBubble = std::make_unique<CStageBubble>();
	CCircle* c = new CCircle;
	cBubble->setShape(c);


	ShapeSetParam param(ShapeSetParam::ParamType::PT_CIRCLE);
	param.param.paramCircle.point = position;
	param.param.paramCircle.r = BUBBLE_RADIUS;

	cBubble->getShape()->paramUpdate(&param);

	CollisionManager::getInstance()->addObject(cBubble.get());

}

void Bubble::fall()
{
	Vector2D vectorX(0.0f, 0.0f + gravity);
	gravity += 0.1f;
	move(vectorX, 1.0f);
	if (WINDOW_HEIGHT + BUBBLE_RADIUS <= getPos().y)
	{
		deactivate();
	}

}


Float2 Bubble::getPos()
{
	return position;
}

void Bubble::move(Vector2D _vec, float speed)
{
	position += _vec * speed;
	rBubble.setBase(position);

	ShapeSetParam param(ShapeSetParam::ParamType::PT_CIRCLE);
	param.param.paramCircle.point = position;
	param.param.paramCircle.r = BUBBLE_RADIUS;

	cBubble->getShape()->paramUpdate(&param);
	

		auto colId = cBubble->getInfoId();
		for (auto& id : colId)
		{
			if (id == INFO_ID_DEFAULT) continue;
			std::weak_ptr<CollisionInfo> info = CollisionManager::getInstance()->getColInfoFromId(id);
			if (!info.lock()) continue;

			if (info.lock()->getEnter())
			{
				if (info.lock()->getTarget(cBubble.get())->getMark() == CollisionObject::WALL && state == STATE::SHOOT)
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
	rBubble.setBase(position);

	ShapeSetParam param(ShapeSetParam::ParamType::PT_CIRCLE);
	param.param.paramCircle.point = position;
	param.param.paramCircle.r = BUBBLE_RADIUS;

	cBubble->getShape()->paramUpdate(&param);
}

bool Bubble::getIsChecked()
{
	return isChecked;
}

bool Bubble::getCanDestroy()
{
	return canDestroy;
}
