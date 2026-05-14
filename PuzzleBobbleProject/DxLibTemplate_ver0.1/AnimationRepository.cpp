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

void AnimationRepository::initAnimationRepository()
{
	ImageManager* pImageManager = ImageManager::getInstance();

	AnimationDataSet* pAds = getAds(AOT_PLAYER_LEFT);
	AnimationData* pAd = pAds->getAnimationData(A_PLAYER_LEFT_IDLE);


	int imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_IDLE);
	pAd->pushSetImage(DerivationGraph(0, 0, 17, 19, imageHandle));
	pAd->pushSetWait(120);
	pAd->pushSetImage(DerivationGraph(17 + 15, 0, 18, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(17 + 15 + 18 + 15, 0, 18, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(1);

	pAd = pAds->getAnimationData(A_PLAYER_LEFT_WIN);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_WIN);
	pAd->pushSetImage(DerivationGraph(0, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 + 12, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 + 12 + 21 + 13, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 + 12 + 21 + 13 + 21 + 13, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(1);

	pAd = pAds->getAnimationData(A_PLAYER_LEFT_RELOAD);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_RELOAD);	
	pAd->pushSetImage(DerivationGraph(0, 0, 17, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(17 + 14, 0, 19, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(17 + 14 + 19 + 13, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(17 + 14 + 19 + 13 + 21 + 13, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(17 + 14 + 19 + 13 + 21 + 13 + 20 + 10, 0, 23, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(1);

	pAd = pAds->getAnimationData(A_PLAYER_LEFT_FAILED);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_FAILED);
	pAd->pushSetImage(DerivationGraph(0, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 + 8, 0, 26, 19, imageHandle));	
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 + 8 + 26 + 8, 0, 25, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 + 8 + 26 + 8 + 25 + 8, 0, 24, 19, imageHandle));
	pAd->pushSetWait(5);

	pAd = pAds->getAnimationData(A_PLAYER_LEFT_OVER);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_OVER);
	pAd->pushSetImage(DerivationGraph(0, 0, 24 ,28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(24 + 8, 0, 25, 28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(24 + 8 + 25 + 8, 0, 25, 28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(24 + 8 + 25 + 8 + 25 + 8, 0, 25, 28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(1);

	pAd = pAds->getAnimationData(A_PLAYER_LEFT_SHOOT);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_LEFT_SHOOT);	
	pAd->pushSetImage(DerivationGraph(0, 0, 17, 18, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(17 + 15, 0, 23, 18, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(17 + 15 + 23 + 10, 0, 23, 18, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(1);


	pAds = getAds(AOT_PLAYER_RIGHT);
	pAd = pAds->getAnimationData(A_PLAYER_RIGHT_IDLE);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_IDLE);

	pAd->pushSetImage(DerivationGraph(0, 0, 19, 19, imageHandle));
	pAd->pushSetWait(120);
	pAd->pushSetImage(DerivationGraph(19 + 13, 0, 19, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(19 + 13 + 19 + 14, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(19 + 13 + 19 + 14 + 20 + 12, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(19 + 13 + 19 + 14 + 20 + 12 + 21 + 10, 0, 22, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(19 + 13 + 19 + 14 + 20 + 12 + 21 + 10 + 22 + 8, 0, 25, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(1);

	pAd = pAds->getAnimationData(A_PLAYER_RIGHT_WIN);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_WIN);

	pAd->pushSetImage(DerivationGraph(0, 0, 20, 19,imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 + 13, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 + 13 + 20 + 13, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 + 13 + 20 + 13 + 20 + 13, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(20 + 13 + 20 + 13 + 20 + 13 + 20 + 12, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(1);

	pAd = pAds->getAnimationData(A_PLAYER_RIGHT_CRANK);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_CRANK);
	pAd->pushSetImage(DerivationGraph(0, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14 + 21 + 12, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14 + 21 + 12 + 21 + 10, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14 + 21 + 12 + 21 + 10 + 20 + 11, 0, 23, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14 + 21 + 12 + 21 + 10 + 20 + 11 + 23 + 8, 0, 23, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14 + 21 + 12 + 21 + 10 + 20 + 11 + 23 + 8 + 23 + 10, 0, 23, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(1);

	pAd = pAds->getAnimationData(A_PLAYER_RIGHT_CRANK_REVERSE);
	pAd->pushSetImage(pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_CRANK));
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_CRANK);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14 + 21 + 12 + 21 + 10 + 20 + 11 + 23 + 8 + 23 + 10, 0, 23, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14 + 21 + 12 + 21 + 10 + 20 + 11 + 23 + 8, 0, 23, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14 + 21 + 12 + 21 + 10 + 20 + 11, 0, 23, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14 + 21 + 12 + 21 + 10, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14 + 21 + 12, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14 + 20 + 14, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(21 + 14, 0, 20, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(0, 0, 21, 19, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(1);


	pAd = pAds->getAnimationData(A_PLAYER_RIGHT_OVER);
	imageHandle = pImageManager->getImageHandle(ImageManager::IMAGE_PLAYER_RIGHT_OVER);
	pAd->pushSetImage(DerivationGraph(0, 0, 22, 28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushSetImage(DerivationGraph(22 + 10, 0, 21, 28, imageHandle));
	pAd->pushSetWait(5);
	pAd->pushJump(1);






	pAd->pushSetWait(5);

	pAd->pushSetWait(5);
	pAd->pushJump(1);



}

AnimationDataSet* AnimationRepository::getAds(int AnimobjectType)
{
	if (AOT_NUM < AnimobjectType)
	{
		return NULL;
	}
	return &ads[AnimobjectType];
}
