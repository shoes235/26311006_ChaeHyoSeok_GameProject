#include "InGameScene.h"

int InGameScene::Init()
{
	SetWindow(false);

	//font
	_font = g2_FontCreate("굴림", 24, 0);

	
	//obj instance
	Flag* blueFlag = new Flag(VEC2{ 250,350 }, E_FlagColorType::BLUE);
	Flag* whiteFlag = new Flag(VEC2{ 1000,350 }, E_FlagColorType::WHITE);

	_objs.push_back(blueFlag);
	_objs.push_back(whiteFlag);

	//Register Input
	_inputMgr.RegisterAction
	(
		{ VK_LEFT,'A' }, 
		[=]()
		{
			blueFlag->ChangeFlag();
		}
	);
	_inputMgr.RegisterAction
	(
		{ VK_RIGHT,'D' },
		[=]()
		{
			whiteFlag->ChangeFlag();
		}
	);


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
	
	_inputMgr.GetKeyDownInput();

	//
	float delta = 0.016f;
	for (auto* i : _objs)
		i->Update(delta);

	
	
	return 0;
}

int InGameScene::Destroy()
{
	for (auto* i : _objs)
		delete i;
	_objs.clear();

	
	return 0;
}