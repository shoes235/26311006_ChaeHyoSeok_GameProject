#pragma once
#include "IScene.h"
#include "GameObject.h"
#include "Flag.h"
#include "InputManager.h"
#include "Timer.h"
#include "Randomizer.h"
#include "ProgressBar.h"

#include <string>
using std::string;

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
	int _commFont = 0;

	//input
	InputManager _inputMgr;

	//=== Games ===

	//Timer
	Timer _timer;

	float _gameTime = 300.0f;
	float _remainGameTime = 0.0f;

	float _commandTime = 5.0f;
	float _remainCommandTime = 0.0f;

	//Progress
	ProgressBar* _bar;

	//command
	E_Command _command = E_Command::BLUE_DOWN;
	string _commText = "";

	//Score
	int _score = 0;
	int _life = 5;

	bool _gameOver = false;

	//Audio
	int _bgm = 0;

private:
	void NextCommand();
	bool CheckAnswer();

	void GiveCommand();

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

