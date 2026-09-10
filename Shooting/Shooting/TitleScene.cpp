#include "TitleScene.h"

int TitleScene::Init()
{
	IScene::Init();

	Randomizer randSys;

	VEC2 zero = { 0,0 };
	_textures.emplace_back("rsc/Babem.png",zero);
	_textures.emplace_back("rsc/cat.jpg",zero);
	_textures.emplace_back("rsc/images.jpg",zero);
	_textures.emplace_back("rsc/very-silly-cat-silly.png",zero);

	for (auto& texture : _textures)
	{
		VEC2 rnPos;
		rnPos.x = randSys.Rand(0, _winSize.cx);
		rnPos.y = randSys.Rand(0, _winSize.cy);

		texture.SetPos(rnPos);
		texture.Load();
	}
	return 0;
}

int TitleScene::Render()
{
	IScene::Render();

	for (auto& texture : _textures) texture.Print();

	return 0;
}