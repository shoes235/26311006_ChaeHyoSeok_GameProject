#include "SceneManager.h"

void SceneManager::ChangeScene(IScene* nextScene, E_SceneType targetType)
{
	if (nextScene == nullptr) return;

	if (nextScene->CheckAndProcess(targetType) == false)
	{
		delete nextScene;
		return;
	}

	if (_curScenePtr != nullptr)
	{
		_curScenePtr->Destroy();
		delete _curScenePtr;
	}

	_curScenePtr = nextScene;
	_curScenePtr->Init();

	_curSceneType = targetType;
}