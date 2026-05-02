#include"AnimationRepository.h"
#include"DxLib.h"


AnimationRepository::AnimationRepository()
{

}

AnimationRepository* AnimationRepository::getInstance()
{
	static AnimationRepository instance;
	return &instance;
}

AnimationDataSet* AnimationRepository::getAds(int AnimobjectType)
{
	if (AOT_NUM < AnimobjectType)
	{
		return NULL;
	}
	return &ads[AnimobjectType];
}
