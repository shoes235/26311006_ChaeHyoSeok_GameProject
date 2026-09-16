#include "AnimationClip.h"
void AnimationClip::AddTexture(Texture* tex) { _textures.push_back(tex); }

Texture* AnimationClip::GetTexture(int idx)
{
	if (_textures.empty()) return nullptr;
	if (idx < 0) idx = 0;
	if (idx > _textures.size()) idx = (int)_textures.size() -1;
	return _textures[idx];
}

int AnimationClip::GetFrameCount() const { return (int)_textures.size(); }
float AnimationClip::GetFrameDuration() const { return _frameDuration; }
bool AnimationClip::IsLoop() const { return _isLoop; }
string AnimationClip::GetName() const { return _clipName; }
