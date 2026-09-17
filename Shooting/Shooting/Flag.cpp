#include "Flag.h"

Flag::Flag(VEC2 pos, E_FlagColorType col)
	: GameObject(pos),_colorType(col)
{
	string prefix = (_colorType == E_FlagColorType::BLUE)?
		"rsc/Flag/Blue/" 
		: "rsc/Flag/White/";


	Texture* upTex = new Texture(prefix + "Up.png", pos);
	upTex->Load();
	AnimationClip* upClip = new AnimationClip("Up", 0.1f, false);
	upClip->AddTexture(upTex);


	Texture* downTex = new Texture(prefix + "Down.png", pos);
	downTex->Load();
	AnimationClip* downClip = new AnimationClip("Down", 0.1f, false);
	downClip->AddTexture(downTex);

	_anim->AddClip("Up", upClip);
	_anim->AddClip("Down", downClip);

	_anim->ChangeClip("Down");
	_isUp = false;
}



void Flag::ChangeFlag()
{
	_isUp = !_isUp;

	if (_isUp)
		_anim->ChangeClip("Up");
	else 
		_anim->ChangeClip("Down");
}

E_FlagColorType Flag::GetColor() const { return _colorType; }
bool Flag::IsUp() const { return _isUp; }