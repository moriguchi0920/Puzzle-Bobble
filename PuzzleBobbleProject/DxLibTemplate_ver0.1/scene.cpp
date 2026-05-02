#include"scene.h"


Scene::Scene()
{
	sceneAlpha = 255;
	transitionFlag = false;
	blackoutFlag = false;
	finishFlag = false;
	nextSceneType = SCENE_DEFAULT;
	soundVolume = 255;
}