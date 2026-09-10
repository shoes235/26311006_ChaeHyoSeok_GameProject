#include "IScene.h"

bool IScene::CheckAndProcess(E_SceneType curType)
{
	if (_sceneType != curType)
	{
		std::cout << "ÇöÀç ¾À != this ¾À -> Destroy" << std::endl;
		Destroy();
		return false;
	}
	return true;
}

int IScene::Init()
{
	//window
	g2_SetClearColor(_winColor);
	g2_InitSdk();
	g2_CreateWin(this->_winPos.x, this->_winPos.y, this->_winSize.cx, this->_winSize.cy, this->_winName.c_str());

	return 0;
}

int IScene::InitSDK()
{
	return 0;
}

//Life-Cycle
int IScene::Update()
{
	return 0;
}
int IScene::Render()
{
	return 0;
}

int IScene::Destroy()
{
	g2_DestroyWin();

	return 0;
}