#pragma once
#include <glc2d.h>
#include "IScene.h"
#include "InGameScene.h"
#include "Texture.h"
#include "Randomizer.h"
#include "InputManager.h"

#include <vector>
using std::vector;

class TitleScene : public IScene
{
public :
	TitleScene() : IScene(E_SceneType::TITLE)
	{
		_winName = "Title 창";
		_winColor = 0x000000; // 검은색
	}
public:
	int Init() override;
	int Render() override;
	int Update() override;
	int Destroy() override;
private:
	vector<Texture*> _textures;
	Texture* _background = new Texture("rsc/MainMenu.png",VEC2(0,0));

	//text
	int nFont = 0;

	//Input
	InputManager _inputMgr;
};

