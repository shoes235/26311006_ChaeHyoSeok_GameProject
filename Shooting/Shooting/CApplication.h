#pragma once
#include <windows.h>
#include <string>
class CApplication
{
//Windows
public:
	CApplication(std::string name, POINT pos, SIZE size)
		: _winName(name), _winPos(pos), _winSize(size) {}

protected :
	std::string _winName;
	POINT _winPos;
	SIZE  _winSize;

public:
	int Init();
	virtual int Update();
	virtual int Render();
	int Destroy();

	int InitSDK();

};

