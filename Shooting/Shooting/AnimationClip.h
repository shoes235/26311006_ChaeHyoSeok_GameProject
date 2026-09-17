#pragma once

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "Texture.h"

class AnimationClip
{
private:
	string _clipName;
	vector<Texture*> _textures;
	float _frameDuration;
	bool _isLoop;
public:
	AnimationClip(string name, float frameDur = 0.1f, bool loop = true)
		: _clipName(name), _frameDuration(frameDur), _isLoop(loop) {}
	~AnimationClip()
	{
		for (auto& t : _textures)
		{
			t->Release();
			delete t;
		}
		_textures.clear();
	}

	void AddTexture(Texture* tex);
	Texture* GetTexture(int idx);

	int GetFrameCount() const;

	float GetFrameDuration() const;
	void SetFrameDuration(float duration);
	
	bool IsLoop() const;
	string GetName() const;

};

