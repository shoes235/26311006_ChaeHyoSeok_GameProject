#pragma once
#include "GameObject.h"

enum class E_FlagColorType
{
	WHITE,
	BLUE
};




class Flag : public GameObject
{
private:
	E_FlagColorType _colorType;
	bool _isUp = false;

public :
	Flag(VEC2 pos, E_FlagColorType col);

	void ChangeFlag();

	E_FlagColorType GetColor() const;
	bool IsUp() const;


};

