#include"collision.h"

// コンストラクタ
CollisionObject::CollisionObject()
{
	pShape = NULL;
	damage = 1;
	for (int i = 0; i < INFO_INDEX_MAX; i++)
	{
		colInfoIdx[i] = INFO_INDEX_DEFAULT;
	}
	isCollide = true;
}
// デストラクタ
CollisionObject::~CollisionObject()
{
	delete(pShape);
	pShape = NULL;

}

void CollisionObject::setInfoIdx(int idx)
{
	for (int i = 0; i < INFO_INDEX_MAX; i++)
	{
		if (colInfoIdx[i] == INFO_INDEX_DEFAULT)
		{
			colInfoIdx[i] = idx;
			break;
		}
	}
}

void CollisionObject::removeInfoIdx(int idx)
{
	for (int i = 0; i < INFO_INDEX_MAX; i++)
	{
		if (colInfoIdx[i] == idx)
		{
			colInfoIdx[i] = INFO_INDEX_DEFAULT;

		}
	}
}
int CollisionObject::getInfoIdx(int i)
{
	return colInfoIdx[i];
}
void CollisionObject::setShape(CollisionShape* _pShape)
{
	pShape = _pShape;
}

CollisionShape* CollisionObject::getShape()
{
	return pShape;
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

 
CollisionObject::CollisionMark CAlly::getMark()
{
	return ALLY;
}
bool CAlly::isCollideTarget(CollisionMark mark)
{
	if (mark == CollisionObject::CollisionMark::ALLY
		|| mark == CollisionObject::CollisionMark::PLATE
		|| mark == CollisionObject::CollisionMark::LAZER
		|| mark == CollisionObject::CollisionMark::BULLET
		)
	{
		return false;
	}
	return true;
}

CollisionObject::CollisionMark CPlate::getMark()
{
	return PLATE;
}
bool CPlate::isCollideTarget(CollisionMark mark)
{
	if (mark == CollisionObject::CollisionMark::ALLY
		|| mark == CollisionObject::CollisionMark::PLATE
		|| mark == CollisionObject::CollisionMark::WALL
		)
	{
		return false;
	}
	return true;
}
CollisionObject::CollisionMark CEnemy::getMark()
{
	return ENEMY;
}
bool CEnemy::isCollideTarget(CollisionMark mark)
{
	if (mark == CollisionObject::CollisionMark::ENEMY
		|| mark == CollisionObject::CollisionMark::WALL
		|| mark == CollisionObject::CollisionMark::ENEMYLAZER
		)
	{
		return false;
	}
	return true;
}

CollisionObject::CollisionMark CWall::getMark()
{
	return WALL;
}
bool CWall::isCollideTarget(CollisionMark mark)
{
	if (mark == CollisionObject::CollisionMark::ENEMY
		|| mark == CollisionObject::CollisionMark::PLATE
		|| mark == CollisionObject::CollisionMark::WALL
		)
	{
		return false;
	}
	return true;
}

CollisionObject::CollisionMark CLazer::getMark()
{
	return LAZER;
}
bool CLazer::isCollideTarget(CollisionMark mark)
{
	if (mark == CollisionObject::CollisionMark::ALLY
		|| mark == CollisionObject::CollisionMark::ENEMYLAZER
		|| mark == CollisionObject::CollisionMark::LAZER
		|| mark == CollisionObject::CollisionMark::BULLET
		)
	{
		return false;
	}
	return true;
}

CollisionObject::CollisionMark CBullet::getMark()
{
	return BULLET;
}
bool CBullet::isCollideTarget(CollisionMark mark)
{
	if (mark == CollisionObject::CollisionMark::BULLET || 
		mark == CollisionObject::CollisionMark::ALLY ||
		mark == CollisionObject::CollisionMark::LAZER)
	{
		return false;
	}
	return true;
}


CollisionObject::CollisionMark CEnemyLazer::getMark()
{
	return ENEMYLAZER;
}
bool CEnemyLazer::isCollideTarget(CollisionMark mark)
{
	if (mark == CollisionObject::CollisionMark::ENEMY
		|| mark == CollisionObject::CollisionMark::ENEMYLAZER
		|| mark == CollisionObject::CollisionMark::LAZER

		)
	{
		return false;
	}
	return true;
}
