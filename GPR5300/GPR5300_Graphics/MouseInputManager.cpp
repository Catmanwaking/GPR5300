#include "MouseInputManager.h"

MouseInputManager* MouseInputManager::pInstance = nullptr;

MouseInputManager* MouseInputManager::GetInstance()
{
    if (pInstance == nullptr)
    {
        pInstance = new MouseInputManager();
    }
    return pInstance;
}

void MouseInputManager::Init()
{
}

void MouseInputManager::DeInit()
{
}

void MouseInputManager::ClearMouseDelta()
{
    mouseDelta.x = 0.0f;
    mouseDelta.y = 0.0f;
}

void MouseInputManager::AddMouseDelta(INT x, INT y)
{
    mouseDelta.x += (FLOAT)x;
    mouseDelta.y += (FLOAT)y;
}
