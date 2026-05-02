#pragma once
#include"AnimationDataSet.h"

class AnimationRepository
{
private :
	AnimationRepository();
	AnimationRepository(const AnimationRepository& other) = delete;
	AnimationRepository& operator = (const AnimationRepository& other) = delete;

public :
	static AnimationRepository* getInstance();

	static enum AnimationObjectType
	{
		AOT_PLAYER_LEFT,
		AOT_PLAYER_RIGHT,
		AOT_BALL_ENEMY,
		AOT_EXPLODE_BULLET,
		AOT_EXPLODE_ENEMY_DEATH,
		AOT_NUM,
	};




private :
	AnimationDataSet ads[AOT_NUM];

public :
	AnimationDataSet* getAds(int AnimobjectType);

};