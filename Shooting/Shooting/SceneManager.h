#pragma once
#include "E_SceneType.h"
#include "IScene.h"

class SceneManager
{
private:
	E_SceneType _curSceneType;
	IScene* _curScenePtr = nullptr;
public :
	const E_SceneType& g_curSceneType;

	SceneManager() : _curSceneType(E_SceneType::TITLE),g_curSceneType(_curSceneType){}

	void ChangeScene(IScene* nextScene, E_SceneType targetType);

};

