#pragma once
#include "IScene.h"

class InGameScene : public IScene
{
public:
	InGameScene() : IScene(E_SceneType::IN_GAME)
	{
		_winName = "InGame";
	}
public:
	int Init() override;
	int Render() override;
	int Update() override;
};

