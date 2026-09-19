#include "JumpScareScene.h"

void JumpScareScene::Init()
{
	SetFullScreen();

	_img->Load();
	
	_sfx = g2_SoundLoad("rsc/audio/SFX/JumpScare.mp3");
	
	return;
}

void JumpScareScene::Update()
{
	float dt = g_deltaTimer.GetDeltaTime();
	_timer += dt;

	if (_timer >= JUMP_SCARE_TIME)
	{
		if(!_trigger)
			g2_SoundPlay(_sfx,false);
		_trigger = true;

	}

	if (_timer >=
		JUMP_SCARE_TIME + SCENE_CHANGE_TIME)
	{
		//g_SceneMgr.ChangeScene()
	}

		return;
}

void JumpScareScene::Render()
{
	if(_trigger)
		_img->Print();

	return;
}