#pragma once
#include"common_type.h"
#include"common_func.h"
#include"debug_color.h"

// 全てのオブジェクトの当たり判定の種類、種類ごとに当たるかどうか、今当たっているかどうか、当たった相手を保存するクラス
class CollisionObject
{

protected:
	// 形オブジェクトのポインタ
	CollisionShape* pShape;

	// CollisionInfo検索用の配列インデックス
	int colInfoIdx[INFO_INDEX_MAX];
	// 当たった時のダメージ
	int damage;
	// 当たり判定をとるかどうか(無敵などの処理用)
	bool isCollide;

	public:
		enum CollisionMark
		{
			DEFAULT = -1,
			ALLY,
			ENEMY,
			PLATE,
			LAZER,
			BULLET,
			ENEMYLAZER,
			WALL,
			COLLISION_MARK_NUM
		};
		
		CollisionObject();
		virtual ~CollisionObject();
		virtual CollisionMark getMark() = 0;
		virtual bool isCollideTarget(CollisionMark mark) = 0;
		void setInfoIdx(int idx);
		void removeInfoIdx(int idx);
		int getInfoIdx(int i);
		CollisionShape* getShape();
		void setShape(CollisionShape* _pShape);
		bool getIsCollide();
		void setDamage(int _damage);
		int getDamage();
		void setIsCollide(bool _isCollide);


public:
		// 当たり判定描画用の色
		DebugColor color;
};

// 味方側当たり判定
class CAlly: public CollisionObject
{
	public: 

		virtual CollisionMark getMark();
		virtual bool isCollideTarget(CollisionMark mark);
};

// 反射板当たり判定
class CPlate : public CollisionObject
{
	public: 
		virtual CollisionMark getMark();
		virtual bool isCollideTarget(CollisionMark mark);

};

// 敵当たり判定
class CEnemy : public CollisionObject
{
	public:
		virtual CollisionMark getMark();
		virtual bool isCollideTarget(CollisionMark mark);


};

// 上下の壁当たり判定
class CWall : public CollisionObject
{
	public:
		virtual CollisionMark getMark();
		virtual bool isCollideTarget(CollisionMark mark);
};

// レーザー当たり判定
class CLazer :public CollisionObject
{
	public:
		virtual CollisionMark getMark();
		virtual bool isCollideTarget(CollisionMark mark);

};

class CBullet : public CollisionObject
{
public:
	virtual CollisionMark getMark();
	virtual bool isCollideTarget(CollisionMark mark);
};

// 敵レーザー当たり判定
class CEnemyLazer :public CollisionObject
{
public:
	virtual CollisionMark getMark();
	virtual bool isCollideTarget(CollisionMark mark);

};



