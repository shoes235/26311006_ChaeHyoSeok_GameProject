#include "SceneManager.h"

int FrameMove()
{
	if (g_SceneMgr.GetCurrentScene() != nullptr)
	{
		g_SceneMgr.GetCurrentScene()->Update();
	}
	return 0;
}

int G_AppRender()
{
	if (g_SceneMgr.GetCurrentScene() != nullptr)
	{
		g_SceneMgr.GetCurrentScene()->Render();
	}
	return 0;
}

void SceneManager::InitEngine()
{
	g2_InitSdk();
	g2_CreateWin(100, 100, 1280, 720, "None");
	
	
	g2_SetRender(G_AppRender);
	g2_SetFrameMove(FrameMove);

}

void SceneManager::Run()
{
	g2_Run();

	if (_curScenePtr != nullptr)
	{
		_curScenePtr->Destroy();
		delete _curScenePtr;
		_curScenePtr = nullptr;
	}
	g2_DestroyWin();
}

void SceneManager::ChangeScene(IScene* nextScene, E_SceneType targetType)
{
	if (nextScene == nullptr)
	{
		std::cout << "전환될씬 null 임다 \n";
		return;
	}

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