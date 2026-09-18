#pragma once
#include "IScene.h"
#include "GameObject.h"
#include "Flag.h"
#include "InputManager.h"
#include "Timer.h"
#include "Randomizer.h"
#include "ProgressBar.h"
#include "GameData.h"

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
	vector<int> _fonts;

	//input
	InputManager _inputMgr;

	//=== Games ===

	//Timer
	Timer _timer;

	float _gameTime = .0f;

	//com time
	float _commandTime = 5.0f;
	float _remainCommandTime = 0.0f;
	const float _minComTime = .5f;

	//bg
	float _bgColTime = 1.0f;
	float _bgRemainColTime = 0.0f;

	//Progress
	ProgressBar* _bar;

	//command
	E_Command _command = E_Command::BLUE_DOWN;
	string _commText = "";

	//Score
	float _score = .0f;
	int _combo = 0;
	float _mult = 1.0f;

	int _life = 5;

	bool _gameOver = false;

	//Audio
	int _bgm = 0;
	int _correctSFX = 0;
	int _wrongSFX = 0;
	int _gameOverSFX = 0;

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

