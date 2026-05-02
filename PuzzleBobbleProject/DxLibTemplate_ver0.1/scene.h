#pragma once
#include"dxlib.h"


class Scene
{
	public:
		enum SceneType
		{
			SCENE_DEFAULT = -1,
			SCENE_TITLE,
			SCENE_SETTING,
			SCENE_TUTORIAL,
			SCENE_GAME,
			SCENE_CLEAR,
			SCENE_NUM
		};
		int sceneAlpha;
		bool transitionFlag;
		bool blackoutFlag;
		bool finishFlag;
		int soundVolume;
		SceneType nextSceneType;
		Scene();

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void exit() = 0;

};