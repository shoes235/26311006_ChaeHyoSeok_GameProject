#include "InGameScene.h"

int InGameScene::Init()
{
	SetWindow(false);

	//font
	_font = g2_FontCreate("굴림", 24, 0);

	
	//obj instance
	_blueFlag = new Flag(VEC2{ 500,350 }, E_FlagColorType::BLUE);
	_whiteFlag = new Flag(VEC2{ 700,350 }, E_FlagColorType::WHITE);

	_objs.push_back(_blueFlag);
	_objs.push_back(_whiteFlag);

	//Register Input
	_inputMgr.RegisterAction
	(
		{ VK_LEFT,'A' }, 
		[=]()
		{
			_blueFlag->ChangeFlag();
		}
	);
	_inputMgr.RegisterAction
	(
		{ VK_RIGHT,'D' },
		[=]()
		{
			_whiteFlag->ChangeFlag();
		}
	);

	//Timer
	_timer.Init();

	_remainGameTime = _gameTime;

	NextCommand();

	return 0;
}
int InGameScene::Render()
{
	IScene::Render();
	

	
	
	//Objs
	for (auto* i : _objs)
		i->Render();

	//Font
	g2_FontDrawText(_font, { 390,10,890,50 }, 0xFF000000, "SPACE 를 눌러 다음 씬으로 이동");


	return 0;
}
int InGameScene::Update()
{
	IScene::Update();
	
	if (_gameOver)
		return 0;

	//Times
	_timer.Update();

	float delta = _timer.GetDeltaTime();

	_remainGameTime -= delta;
	_remainCommandTime -= delta;

	//Input
	_inputMgr.GetKeyDown();

	//Obj
	float delta = 0.016f;
	for (auto* i : _objs)
		i->Update(delta);

	//Time 종료
	if (_remainCommandTime <= 0.0f)
	{
		if (CheckAnswer())
			_score++;
		else
			_life--;

		if (_life <= 0)
		{
			_gameOver = true;
			return 0;
		}

		NextCommand();
	}

	if (_remainGameTime <= 0.0f)
	{
		_remainGameTime = 0.0f;
		_gameOver = true;
	}


	
	return 0;
}

int InGameScene::Destroy()
{
	for (auto* i : _objs)
		delete i;
	_objs.clear();

	
	return 0;
}

void InGameScene::NextCommand()
{
	Randomizer randSys;

	int comm = randSys.Rand(0, 4);

	_command = static_cast<E_Command>(comm);

	_commandTime = GetCommandLimitTime();

	_remainCommandTime = _commandTime;
}

float InGameScene::GetCommandLimitTime()
{
	float progress = 1.0f - (_remainGameTime / _gameTime);

	float time = 5.0f - progress * 4.0f;

	if (time < 1.0f)
		time = 1.0f;

	return time;
}

bool InGameScene::CheckAnswer()
{
	switch (_command)
	{
	case E_Command::BLUE_UP:
		return _blueFlag->IsUp();
	case E_Command::BLUE_DOWN:
		return !_blueFlag->IsUp();
	case E_Command::WHITE_UP:
		return _whiteFlag->IsUp();
	case E_Command::WHITE_DOWN:
		return !_whiteFlag->IsUp();
	}

	return false;
}