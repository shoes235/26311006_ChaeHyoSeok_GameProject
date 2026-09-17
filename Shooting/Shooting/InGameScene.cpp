#include "InGameScene.h"

int InGameScene::Init()
{
	SetWindow(false);

	//Audio
	_bgm = g2_SoundLoad("rsc/audio/Glorious Morning.mp3");
	g2_SoundPlay(_bgm, true);

	_correctSFX = g2_SoundLoad("rsc/audio/SFX/correct.mp3");
	_wrongSFX = g2_SoundLoad("rsc/audio/SFX/wrong.mp3");


	//font
	_font = g2_FontCreate("굴림", 24, 0);
	_commFont = g2_FontCreate("굴림", 126, 0);

	
	//obj instance
	_blueFlag = new Flag(VEC2{ 500,350 }, E_FlagColorType::BLUE);
	_whiteFlag = new Flag(VEC2{ 700,350 }, E_FlagColorType::WHITE);

	_bar = new ProgressBar(VEC2{ 370,15 });

	_objs.push_back(_blueFlag);
	_objs.push_back(_whiteFlag);
	_objs.push_back(_bar);

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

	_inputMgr.RegisterAction
	(
		{ VK_ESCAPE,'D' },
		[=]()
		{
			_gameOver = true;
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

	GiveCommand();

	//Font
	if (!_gameOver)
	{
		//comm
		g2_FontDrawText
		(
			_commFont,
			{ 400,150,1280,300 },
			0xFF000000,
			_commText.c_str());
	}
	
	//Time
	g2_FontDrawText
	(
		_font,
		{ 550,50,890,90 },
		0xFFFFFFFF,
		"Time Left : %.1f", _remainCommandTime
	);

	g2_FontDrawText
	(
		_font,
		{ 20,20,250,60 },
		0xFF000000,
		"Game Time : %.1f", _remainGameTime
	);

	//Score

	g2_FontDrawText
	(
		_font,
		{ 20,60,250,100 },
		0xFF000000,
		"Score : %1d", _score
	);

	//Life
	g2_FontDrawText
	(
		_font,
		{ 20, 100, 300, 200 },
		0xFF000000,
		"LIFE : %1d",_life
	);

	g2_FontDrawText
	(
		_font,
		{ 20, 650,500, 800},
		0xFF000000,
		"ESC : 종료 / <- : 청기 / -> : 백기"
	);


	//종료
	if (_gameOver)
	{
		g2_FontDrawText
		(
			_commFont,
			{ 300, 100, 1200, 220 },
			0xFFFF0000,
			"GAME OVER"
		);
	}





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
	for (auto* i : _objs)
		i->Update(delta);

	//Time 종료
	if (_remainCommandTime < 0.0f)
	{
		if (CheckAnswer())
		{
			g2_SoundPlay(_correctSFX, false);
			_score++;

			//bg
			SetWindowColor(0xFF00FF00);

			_bgRemainColTime = _bgColTime;

		}
		else
		{
			g2_SoundPlay(_wrongSFX, false);
			_life--;

			//bg
			SetWindowColor(0xFFFF0000);

			_bgRemainColTime = _bgColTime;
		}
		if (_life <= 0)
		{
			_gameOver = true;
			return 0;
		}

		NextCommand();
	}

	if (_bgRemainColTime > 0.0f)
	{
		_bgRemainColTime -= delta;

		if (_bgRemainColTime <= 0.0f)
		{
			_bgRemainColTime = 0.0f;
			SetWindowColor(0xFFFFFFFF);
		}
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

	g2_SoundRelease(_bgm);
	g2_SoundRelease(_correctSFX);
	g2_SoundRelease(_wrongSFX);

	return 0;
}

void InGameScene::NextCommand()
{

	Randomizer randSys;

	int comm = randSys.Rand(0, 3);

	_command = static_cast<E_Command>(comm);

	_commandTime = GetCommandLimitTime();

	_remainCommandTime = _commandTime;

	_bar->SetTime(_commandTime);
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

void InGameScene::GiveCommand()
{
	switch (_command)
	{
	case E_Command::BLUE_UP:
		_commText = "청기 올려";
		break;
	case E_Command::BLUE_DOWN:
		_commText = "청기 내려";
		break;
	case E_Command::WHITE_UP:
		_commText = "백기 올려";
		break;
	case E_Command::WHITE_DOWN:
		_commText = "백기 내려";
		break;
	}
}
