#pragma once
#include "IScene.h"
#include "GameObject.h"
#include "Flag.h"
#include "InputManager.h"
#include "Timer.h"
#include "Randomizer.h"

#include <vector>
using std::vector;

enum class E_Command
{
	BLUE_UP,
	BLUE_DOWN,
	WHITE_UP,
	WHITE_DOWN
};




class InGameScene : public IScene
{
private:
	//obj
	vector<GameObject*> _objs;

	Flag* _blueFlag = nullptr;
	Flag* _whiteFlag = nullptr;

	//font
	int _font = 0;

	//input
	InputManager _inputMgr;

	//=== Games ===

	//Timer
	Timer _timer;

	float _gameTime = 60.0f;
	float _remainGameTime = 0.0f;

	float _commandTime = 5.0f;
	float _remainCommandTime = 0.0f;

	//command
	E_Command _command;

	//Score
	int _score = 0;
	int _life = 5;

	bool _gameOver = false;

private:
	void NextCommand();
	bool CheckAnswer();

	float GetCommandLimitTime();
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

