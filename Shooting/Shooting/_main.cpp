#include <iostream>

#include <glc2d.h>
#include "SceneManager.h"

#include "TitleScene.h"

SceneManager g_SceneMgr;

// link the 2d game library
#if defined(_DEBUG)
#if defined(_M_X64) // 64-bit 아키텍처
#pragma comment(lib, "glc2d_x64_debug.lib")
#elif defined(_M_IX86) // 32-bit 아키텍처
#pragma comment(lib, "glc2d_win32_debug.lib")
#endif
#else
#if defined(_M_X64)
#pragma comment(lib, "glc2d_x64_release.lib")
#elif defined(_M_IX86)
#pragma comment(lib, "glc2d_win32_release.lib")
#endif
#endif

//Life Cycle
void main()
{
	g_SceneMgr.InitEngine();

	TitleScene* title = new TitleScene();
	g_SceneMgr.ChangeScene(title, E_SceneType::TITLE);

	//Life::Update
	
	g_SceneMgr.Run();
}