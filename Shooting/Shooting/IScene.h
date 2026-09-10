#pragma once
#include "E_SceneType.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <glc2d.h>

class IScene
{
protected:
	E_SceneType _sceneType;

	//windows Setting
	std::string _winName = "None";
	POINT _winPos{ 0,0 };
	SIZE  _winSize {1280,720};
	unsigned int _winColor = 0x000000;

public:
	IScene(E_SceneType type) : _sceneType(type){}
	virtual ~IScene() {}

	//Birth
	virtual int Init();
	virtual int InitSDK();

	//Life-Cycle
	virtual int Update();
	virtual int Render();

	//Death
	virtual int Destroy();

	bool CheckAndProcess(E_SceneType curType);
};

