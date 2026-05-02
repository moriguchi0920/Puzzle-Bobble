#include"sceneManager.h"

SceneManager::SceneManager()
{
	pRunningScene = new TitleScene;
	pRunningScene->init();
	shadeAlpha = 0;
	soundVolume = 255;
}

void SceneManager::setBrightness(int _shadeAlpha)
{
	shadeAlpha = _shadeAlpha;
}

void SceneManager::setVolume(int _volume)
{
	soundVolume = _volume;
}



SceneManager* SceneManager::getInstance()
{
	static SceneManager instance;
	return &instance;
}

void SceneManager::changeScene(Scene::SceneType type)
{
	pRunningScene->exit();
	delete(pRunningScene);
	pRunningScene = NULL;

	switch (type)
	{
	case Scene::SCENE_TITLE:
		pRunningScene = new TitleScene;
		pRunningScene->init();
		break;
	case Scene::SCENE_SETTING:
		pRunningScene = new SettingScene;
		pRunningScene->init();
		break;
	case Scene::SCENE_TUTORIAL:
		pRunningScene = new TutorialScene;
		pRunningScene->init();
		break;
	case Scene::SCENE_GAME:
		pRunningScene = new GameScene;
		pRunningScene->init();
		break;

	case Scene::SCENE_CLEAR:
		pRunningScene = new ClearScene;
		pRunningScene->init();
		break;
	}
}
void SceneManager::sceneUpdate()
{
	if (pRunningScene->transitionFlag)
	{
		changeScene(pRunningScene->nextSceneType);
	}
}

void SceneManager::sceneExit()
{
	if (pRunningScene != NULL)
	{
		pRunningScene->exit();
		delete(pRunningScene);
	}
}