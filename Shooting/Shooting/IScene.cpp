#include "IScene.h"

int IScene::SetWindow(bool setWinPos)
{
	HWND hwnd = GetActiveWindow();

	if (hwnd != nullptr)
	{
		int x = _winPos.x; int y = _winPos.y;
		if (!setWinPos)
		{
			RECT rect;
			GetWindowRect(hwnd, &rect);
			x = rect.left;
			y = rect.top;
		}

		MoveWindow
		(
			hwnd,
			x,
			y,
			_winSize.cx,
			_winSize.cy,
			TRUE
		);
	}

	g2_SetWindowTitle(_winName.c_str());
	g2_SetClearColor(_winColor);

	return 0;
}

void IScene::SetWindowColor(unsigned int col)
{
	_winColor = col;
	g2_SetClearColor(_winColor);
}


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
	SetWindow();

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
	return 0;
}