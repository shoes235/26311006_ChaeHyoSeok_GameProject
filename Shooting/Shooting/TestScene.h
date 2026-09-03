#pragma once
#include "CApplication.h"
#include <glc2d.h>
#include <string>
class TestScene : public CApplication
{
public : 
	TestScene() : CApplication("cat", { 0,0 }, { 1280,720 }) 
	{
		
	}

public :
	int Render() override;
public :
	int LoadTexture();
	int RelaseTexture();

protected : 
	std::string _filePath = "rsc/cat.jpg";
	int _cat = -1;
	VEC2 _catPos{ 0,0 };

};

