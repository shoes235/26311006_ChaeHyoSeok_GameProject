#include "TestScene.h"
int TestScene::LoadTexture()
{
	_cat = g2_TextureLoad(_filePath.c_str());
	return 0;
}
int TestScene::RelaseTexture()
{
	g2_TextureRelease(_cat);
	return 0;
}

int TestScene::Render()
{

	VEC2 pos(_catPos);
	g2_DrawAlphaOption(1);
	g2_Draw2D(_cat, nullptr, &pos);
	g2_DrawAlphaOption(0);
	return 0;
}