#include "PlayerController.h"
#include "Utils.h"
#include <WinUser.h>

using namespace Constants;

INT PlayerController::Init()
{
	GetCursorPos(&lastPos);
	pMouseInputManager = MouseInputManager::GetInstance();
	pTime = Time::GetInstance();
	return 0;
}

void PlayerController::Update()
{
	FLOAT time = pTime->GetDeltaTime();
	//Vector2 delta = pMouseInputManager->GetMouseDelta();

	GetCursorPos(&pos);
	Vector2 delta = { FLOAT(pos.x - lastPos.x), FLOAT(pos.y - lastPos.y) };
	delta *= (time * sensitivity * toRadian);
	pTransform->rotation.z += delta.y; //TODO WRONG!!!!
	pTransform->rotation.y += delta.x;
	lastPos = { 500, 500 };
	SetCursorPos(500, 500);
}

void PlayerController::DeInit()
{
}
