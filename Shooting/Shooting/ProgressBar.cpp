#include "ProgressBar.h"

ProgressBar::ProgressBar(VEC2 pos)
	: GameObject(pos)
{
	string prefix = "rsc/ProgressBar/Bar_";

	vector<Texture*> texes(5);

	for(int i = 0; i < texes.size(); i++)
	{
		texes[i] = new Texture(prefix + std::to_string(i) + ".png", pos);
		texes[i]->Load();
	}

	_progressClip = new AnimationClip("Progress", 0.1f, false);

	for (auto& tex : texes)
		_progressClip->AddTexture(tex);

	_anim->AddClip("Progress", _progressClip);
	_anim->ChangeClip("Progress");
}


void ProgressBar::SetTime(float time)
{
	int frameCount = _progressClip->GetFrameCount();

	if (frameCount <= 1)
		return;

	float frameDur = time / (frameCount - 1);

	_progressClip->SetFrameDuration(frameDur);

	_anim->Restart();
}