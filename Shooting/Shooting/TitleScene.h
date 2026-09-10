#pragma once
#include "IScene.h"
#include "Texture.h"
#include "Randomizer.h"

#include <vector>
using std::vector;

class TitleScene : public IScene
{
public :
	TitleScene() : IScene(E_SceneType::TITLE)
	{
		
	}
public:
	int Init() override;
	int Render() override;
protected:
	vector<Texture> _textures;
};

