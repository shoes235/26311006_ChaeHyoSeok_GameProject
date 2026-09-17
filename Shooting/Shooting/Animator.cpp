#include "Animator.h"

void Animator::AddClip(const string& name, AnimationClip* clip)
{
	_clips[name] = clip;
	if (_curClip == nullptr)
		_curClip = clip;
}
void Animator::ChangeClip(const string& name)
{
	auto it = _clips.find(name);
	if (it != _clips.end()
		&& _curClip != it->second)
	{
		_curClip = it->second;
		_curFrameIdx = 0;
		_accumulatedTime = 0.0f;
	}
}
void Animator::Play(float delta)
{
	//카운트 0? 클립 NULL?
	if (!_curClip || !_curClip->GetFrameCount()) return;

	_accumulatedTime += delta;

	if (_accumulatedTime >= _curClip->GetFrameDuration())
	{
		_accumulatedTime = 0.0f;
		_curFrameIdx++;

		if (_curFrameIdx >= _curClip->GetFrameCount())
		{
			if (_curClip->IsLoop())
				_curFrameIdx = 0;
			else
				_curFrameIdx = _curClip->GetFrameCount() - 1;
		}
	}
}
Texture* Animator::GetCurrentTexture()
{
	if (!_curClip) return nullptr;

	if (_curFrameIdx < 0 || _curFrameIdx >= _curClip->GetFrameCount()) return nullptr;
	return _curClip->GetTexture(_curFrameIdx);
}