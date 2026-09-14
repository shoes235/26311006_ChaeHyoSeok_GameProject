#include "InputManager.h"
int InputManager::RegisterAction(const vector<unsigned char>& keys, function<void()> callback)
{
	_bindings.push_back({keys,callback});

	return 0;
}

int InputManager::GetInput()
{
	const KEYCODE* pkey = g2_GetKeyboard();
	if (!pkey) return 0;

	for (const auto& bind : _bindings)
	{
		bool isTriggered = true;

		for (auto key : bind.keys)
		{
			if (!pkey[key])
			{
				isTriggered = false;
				break;
			}


		}
		if (isTriggered) bind.callback();
	}

	return 0;
}