#include"collision.h"

// コンストラクタ
CollisionObject::CollisionObject()
{
	damage = 1;
	isCollide = true;
}
// デストラクタ
CollisionObject::~CollisionObject()
{


}

void CollisionObject::setInfoIdx(int idx)
{
	colInfoIdx.push_back(idx);
}

void CollisionObject::removeInfoIdx(int idx)
{
	auto it = std::find(colInfoIdx.begin(), colInfoIdx.end(), idx);
	if (it == colInfoIdx.end()) return;
	colInfoIdx.erase(it);
}
std::vector<int> CollisionObject::getInfoIdx()
{


	return colInfoIdx;
}
void CollisionObject::setShape(CollisionShape* _pShape)
{
	pShape.reset(_pShape);
}

CollisionShape* CollisionObject::getShape()
{
	return pShape.get();
}

void CollisionObject::setIsCollide(bool _isCollide)
{
	isCollide = _isCollide;
}

bool CollisionObject::getIsCollide()
{
	return isCollide;
}



void CollisionObject::setDamage(int _damage)
{
	damage = _damage;
}
int CollisionObject::getDamage()
{
	return damage;
}

CollisionObject::CollisionMark CWall::getMark()
{
	return CollisionMark::WALL;
}

bool CWall::isCollideTarget(CollisionMark mark)
{
	bool ret = false;

	if (mark == CollisionMark::BUBBLE)
	{
		ret = true;
	}

	return ret;
}

CollisionObject::CollisionMark CCeiling::getMark()
{
	return CollisionMark::CEILING;
}

bool CCeiling::isCollideTarget(CollisionMark mark)
{
	bool ret = false;

	if (mark == CollisionMark::BUBBLE)
	{
		ret = true;
	}

	return ret;

}

CollisionObject::CollisionMark CBubble::getMark()
{
	return CollisionMark::BUBBLE;
}

bool CBubble::isCollideTarget(CollisionMark mark)
{
	bool ret = false;

	if (mark == CollisionMark::BUBBLE || mark == CollisionMark::WALL || mark == CollisionMark::CEILING)
	{
		ret = true;
	}

	return ret;

}
