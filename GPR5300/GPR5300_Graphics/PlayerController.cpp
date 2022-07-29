#include "PlayerController.h"
#include "Utils.h"
#include "Vector2.h"
#include "Math.h"

using namespace Constants;

INT PlayerController::Init(UINT width, UINT height)
{
	pTime = Time::GetInstance();
	screenCenter.x = width >> 1;
	screenCenter.y = height >> 1;

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
	pTransform->rotation.z += mouseDelta.y; //TODO wrong axis;
	pTransform->rotation.y += mouseDelta.x;
	SetCursorPos(screenCenter.x, screenCenter.y);

	pTransform->rotation.z = Math::Clamp(pTransform->rotation.z, -XM_PIDIV2, XM_PIDIV2);
}
