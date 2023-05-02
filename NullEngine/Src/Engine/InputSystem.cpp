#include <PCH.h>
#include <Engine/InputSystem.h>
#include <Windows.h>

uint EventSystem::type = 0;
uint EventSystem::state = 0;
POINT EventSystem::pos{};
POINT EventSystem::lastPos{};
POINT EventSystem::delta{};

uint EventSystem::HookMsg(const MSG* msg)
{
    switch (msg->message)
    {

    case WM_LBUTTONDOWN: {
        type = MouseEvent::LPRESS;
    }break;
    case WM_LBUTTONUP: {
        type = MouseEvent::LRELEASE;
    }break;
    case WM_RBUTTONDOWN: {
        type = MouseEvent::RPRESS;
    }break;
    case WM_RBUTTONUP: {
        type = MouseEvent::RRELESE;
    }break;

    case WM_MOUSEMOVE: {
        //type = MouseEvent::MOVE;
        //pos = { LOWORD(msg->lParam), HIWORD(msg->lParam) };
        //state = msg->wParam;
    }break;
    default:
        type = MouseEvent::NONE;
        break;
    }
    return 0;  //is not process here 1 is we ownded this event
}

bool EventSystem::IsKeyDown(int keyCode)
{
    return ::GetAsyncKeyState(keyCode) && 0x8000;
}
