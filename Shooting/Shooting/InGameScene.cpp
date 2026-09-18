#include "InGameScene.h"

int InGameScene::Init()
{
	SetWindow(false);

	//SetData
	GameData::g_score = 0.0f;
	
	//Audio
	_bgm = g2_SoundLoad("rsc/audio/Glorious Morning.mp3");
	g2_SoundPlay(_bgm, true);

	_correctSFX = g2_SoundLoad("rsc/audio/SFX/correct.mp3");
	_wrongSFX = g2_SoundLoad("rsc/audio/SFX/wrong.mp3");
	_gameOverSFX = g2_SoundLoad("rsc/audio/SFX/GameOver.mp3");

	//font
	_fonts.push_back(g2_FontCreate("굴림", 24, 0));
	_fonts.push_back(g2_FontCreate("굴림", 48, 0));
	_fonts.push_back(g2_FontCreate("굴림", 126, 0));
	
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
		{ VK_ESCAPE },
		[=]()
		{
			_gameOver = true;
		}
	);

	//Timer
	_timer.Init();

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
			_fonts[2],
			{ 400,150,1280,300 },
			0xFF000000,
			_commText.c_str());
	}
	
	//Time
	g2_FontDrawText
	(
		_fonts[0],
		{ 550,50,890,90 },
		0xFFFFFFFF,
		"Time Left : %.1f", _remainCommandTime
	);

	//Score

	g2_FontDrawText
	(
		_fonts[2],
		{ 1050,40,1260,200 },
		0xFF000000,
		"%d", (int)_score
	);

	g2_FontDrawText
	(
		_fonts[1],
		{ 1080,200,1260,400 },
		0xFF000000,
		"X %.1f", _mult
	);


	//Life
	g2_FontDrawText
	(
		_fonts[0],
		{ 20, 100, 300, 200 },
		0xFF000000,
		"LIFE : %1d",_life
	);

	g2_FontDrawText
	(
		_fonts[0],
		{ 20, 650,500,700},
		0xFF000000,
		"ESC : 종료 / <- : 청기 / -> : 백기"
	);


	//종료
	if (_gameOver)
	{
		g2_FontDrawText
		(
			_fonts[2],
			{ 300, 100, 1200, 220 },
			0xFFFFFFFF,
			"GAME OVER"
		);

		return 0;

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

	_gameTime += delta;
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
			_combo++;
			_mult = 1.0f + (_combo / 5) * .5f;
			_score += _mult;


			//Sound
			g2_SoundPlay(_correctSFX, false);

			//bg
			SetWindowColor(0xFF00FF00);

			_bgRemainColTime = _bgColTime;

		}
		else
		{
			_combo = 0;
			_mult = 1.0f;
			_life--;

			g2_SoundPlay(_wrongSFX, false);

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
	
	if (_gameOver)
	{
		g2_SoundPlay(_gameOverSFX, false);
		return 0;
	}

	return 0;
}

int InGameScene::Destroy()
{
	GameData::g_score = _score;


	for (auto* i : _objs)
		delete i;
	_objs.clear();
	
	_blueFlag = nullptr;
	_whiteFlag = nullptr;
	_bar = nullptr;


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
	float time = 5.0f - (_gameTime * 0.01f);

	if (time < _minComTime)
		time = _minComTime;

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
