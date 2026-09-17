#pragma once
#include "IScene.h"
#include "GameObject.h"
#include "Flag.h"
#include "InputManager.h"

#include <vector>
using std::vector;

class InGameScene : public IScene
{
private:
	vector<GameObject*> _objs;

	int _font = 0;

	InputManager _inputMgr;
public:
	InGameScene() : IScene(E_SceneType::IN_GAME)
	{
		_winName = "InGame";
		_winColor = 0xFFFFFF;
	}
public:
	int Init() override;
	int Render() override;
	int Update() override;
	int Destroy() override;
};

