#pragma once
#include "scene.h"


class SceneManager
{
public:

	
	// 現在表示しているシーン
	Scene* pRunningScene;

	int shadeAlpha;
	int soundVolume;

private:
	SceneManager();
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator = (const SceneManager& other) = delete;

public:

	static SceneManager* getInstance();

	void setBrightness(int _shadeAlpha);
	void setVolume(int _volume);

	// シーン変更関数
	void changeScene(Scene::SceneType type);
	// シーンの更新
	void sceneUpdate();

	// 終了
	void sceneExit();
};


