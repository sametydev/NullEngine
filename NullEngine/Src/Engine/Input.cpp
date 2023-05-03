#include <PCH.h>
#include <Engine/Input.h>
#include <Windows.h>

uint Input::type = 0;
uint Input::state = 0;
vec2f Input::pos;
vec2f Input::lastPos;
vec2f Input::delta;

uint Input::HookMsg(const MSG* msg)
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
        type = MouseEvent::MOVE;
        pos = { (float)LOWORD(msg->lParam), (float)HIWORD(msg->lParam) };
        state = msg->wParam;
        if (lastPos != pos) {
            delta = lastPos - pos;
        }
        else {
            delta = vec2f();
        }
        lastPos = pos;
    }break;
    default:
        type = MouseEvent::NONE;
        break;
    }
    return 0;  //is not process here 1 is we ownded this event
}

void Input::DiscardEvents()
{
    type = MouseEvent::NONE;
}

bool Input::IsKeyDown(int keyCode)
{
    return ::GetAsyncKeyState(keyCode) && 0x8000;
}