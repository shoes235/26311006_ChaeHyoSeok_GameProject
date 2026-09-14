#include "TitleScene.h"


int TitleScene::Init()
{
	IScene::Init();

	nFont = g2_FontCreate("굴림", 24, 0);

	_inputMgr.RegisterAction(
		{VK_SPACE},
		[=]() {
			InGameScene* nextScene = new InGameScene();
			g_SceneMgr.ChangeScene(nextScene, E_SceneType::IN_GAME);
		}
		);

	VEC2 zero = { 0,0 };

	_textures.emplace_back("rsc/Babem.png",zero);
	_textures.emplace_back("rsc/cat.jpg",zero);
	_textures.emplace_back("rsc/images.jpg",zero);
	_textures.emplace_back("rsc/very-silly-cat-silly.png",zero);

	_background.Load();
	for (auto& texture : _textures)	texture.Load();

	return 0;
}

int TitleScene::Update()
{
	_inputMgr.GetInput();

	//텍스쳐 랜덤 이동
	Randomizer randSys;

	for (auto& texture : _textures)
	{
		VEC2 rnPos;
		rnPos.x = randSys.Rand(0, _winSize.cx);
		rnPos.y = randSys.Rand(0, _winSize.cy);
		texture.SetPos(rnPos);
	}

	return 0;
}

int TitleScene::Render()
{
	IScene::Render();

	Randomizer randSys;

	_background.Print();

	for (auto& texture : _textures) texture.Print();

	g2_FontDrawText(nFont, { 10,10,500,40 }, 0xFFFFFFFF, "SPACE 를 눌러 다음 씬으로 이동");

	return 0;
}

int TitleScene::Destroy()
{
	_background.Release();
	for (auto& texture : _textures) texture.Release();

	return 0;
}