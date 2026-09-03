#include "CApplication.h"
#include <glc2d.h>
int CApplication::Init()
{
	g2_SetClearColor(0x000000);
	g2_InitSdk();
	g2_CreateWin(this->_winPos.x,this->_winPos.y,this->_winSize.cx,this->_winSize.cy,this->_winName.c_str());

	//g2_TextureLoad();

	return 0;
}
int CApplication::Update()
{
	return 0;

}
int CApplication::Render()
{
	return 0;
}
int CApplication::Destroy()
{
	g2_DestroyWin();
	return 0;

}

int CApplication::InitSDK()
{
	g2_InitSdk();
	return 0;
}