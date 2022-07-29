#pragma once
#include "Vector2.h"

class MouseInputManager
{
public:
	static MouseInputManager* GetInstance();
	void Init();
	void DeInit();
	Vector2 GetMouseDelta() const { return mouseDelta; };
	void ClearMouseDelta();
	void AddMouseDelta(INT x, INT y);

private:
	static MouseInputManager* pInstance;
	Vector2 mouseDelta = {};
	Vector2 lastPos = {};
};

