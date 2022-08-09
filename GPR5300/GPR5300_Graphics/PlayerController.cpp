#include "PlayerController.h"
#include "Utils.h"
#include "Vector2.h"
#include "Math.h"

using namespace Constants;

INT PlayerController::Init()
{
	pTime = Time::GetInstance();
	screenCenter.x = GetSystemMetrics(SM_CXSCREEN) >> 1;
	screenCenter.y = GetSystemMetrics(SM_CYSCREEN) >> 1;

	SetCursorPos(screenCenter.x, screenCenter.y);
	ShowCursor(false);
	return 0;
}

void PlayerController::Update()
{
	FLOAT time = pTime->GetDeltaTime();
	Move(time);
	Rotate(time);
}

void PlayerController::DeInit()
{
	ShowCursor(true);
	pTime = nullptr;
}

void PlayerController::Move(FLOAT time)
{
	Vector3 movement;
	if (GetAsyncKeyState('W') & 0x8000) movement.z += 1.0f;
	if (GetAsyncKeyState('S') & 0x8000) movement.z += -1.0f;
	if (GetAsyncKeyState('D') & 0x8000) movement.x += 1.0f;
	if (GetAsyncKeyState('A') & 0x8000) movement.x += -1.0f;
	if (GetAsyncKeyState('E') & 0x8000) movement.y += 1.0f;
	if (GetAsyncKeyState('Q') & 0x8000) movement.y += -1.0f;

	movement.Normalize();
	movement *= moveSpeed * time;

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000) movement *= speedModifier;
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000) movement *= 1 / speedModifier;

	pTransform->position += pTransform->Right() * movement.x;
	pTransform->position += pTransform->Up() * movement.y;
	pTransform->position += pTransform->Forward() * movement.z;
}

void PlayerController::Rotate(FLOAT time)
{
	GetCursorPos(&pos);
	Vector2 mouseDelta = { FLOAT(pos.x - screenCenter.x), FLOAT(pos.y - screenCenter.y) };
	mouseDelta *= (time * sensitivity * toRadian);

	camRotation.y += mouseDelta.x;
	camRotation.x += mouseDelta.y;
	camRotation.x = Math::Clamp(camRotation.x, -XM_PIDIV2, XM_PIDIV2);
	pTransform->rotation = Quaternion(camRotation);

	SetCursorPos(screenCenter.x, screenCenter.y);
}
