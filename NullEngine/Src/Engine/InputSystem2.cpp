#include <PCH.h>
#include <Engine/InputSystem2.h>

InputSystem2::InputSystem2()
{
}

InputSystem2::~InputSystem2()
{
}

void InputSystem2::Update()
{
    POINT currMousePos = {};
    ::GetCursorPos(&currMousePos);

    if (currMousePos.x != oldMousePosition.x || currMousePos.y != oldMousePosition.y)
    {
        deltaMousePosition = vec2f(
            (float)currMousePos.x - (float)oldMousePosition.x,
            (float)currMousePos.y - (float)oldMousePosition.y
        );
    }
    else {
        deltaMousePosition = vec2f(0, 0);
    }
    if (!cursorLocked) {
        oldMousePosition = vec2f(currMousePos.x, currMousePos.y);
    }
    else
    {
        SetCursorPos((int)lockAreaCenter.x, (int)lockAreaCenter.y);
        oldMousePosition = lockAreaCenter;
    }


    for (unsigned int i = 0; i < 256; i++)
    {
        m_keyState[i] = ::GetAsyncKeyState(i);
        //If is key down 0x80
        if (m_keyState[i] & 0x8001)
        {
            m_finalKeyState[i] = 0;
        }
        //Key is up
        else
        {
            if (m_keyState[i] != m_oldKeyState[i])
            {
                m_finalKeyState[i] = 1;
            }
            else
            {
                m_finalKeyState[i] = 2;
            }
        }
    }
    //Storing current key states to old keys state buffer
    ::memcpy(m_oldKeyState, m_keyState, sizeof(short)*256);

    horizontalAxis = 0.0f;
    verticalAxis = 0.0f;

    if (GetKeyDown(NKey::W)) {
        horizontalAxis = 1.0f;
    }
    if (GetKeyDown(NKey::S)) {
        horizontalAxis = -1.0f;
    }
    if (GetKeyDown(NKey::A)) {
        verticalAxis = -1.0f;
    }
    if (GetKeyDown(NKey::D)) {
        verticalAxis = 1.0f;
    }
}

bool InputSystem2::GetKeyDown(const NKey& key)
{
    return (m_finalKeyState[GetInternalKeyCode(key)] == 0);
}

bool InputSystem2::GetKeyUp(const NKey& key)
{
    return (m_finalKeyState[GetInternalKeyCode(key)] == 1);
}

bool InputSystem2::GetKey(const NKey& key)
{
    return 3;
}

void InputSystem2::LockCursor(bool lock)
{
    cursorLocked = lock;
    ShowCursor(!lock);
}

//void InputSystem2::SetLockArea(const Rect& Area)
//{
//    lockArea = Area;
//    lockAreaCenter = Vector2(floor(Area.left + (float)Area.width / 2.0f), floor(Area.top + (float)Area.height / 2.0f));
//}

float InputSystem2::GetAxis(const char* axis)
{
    if (axis == "Horizontal") {
        return horizontalAxis;
    }
    else if (axis == "Vertical") {
        return verticalAxis;
    }
    return 0.0f;
}

vec2f InputSystem2::GetDeltaMouse()
{
    return deltaMousePosition;
}

short InputSystem2::GetInternalKeyCode(const NKey& key)
{
    short KeyWin = 0;

    if (key >= NKey::A && key <= NKey::Z)
    {
        KeyWin = 'A' + ((short)key - (short)NKey::A);
    }
    else if (key >= NKey::N0 && key <= NKey::N9)
    {
        KeyWin = '0' + ((short)key - (short)NKey::N0);

    }
    else if (key == NKey::Shift)
    {
        KeyWin = VK_SHIFT;
    }
    else if (key == NKey::Escape)
    {
        KeyWin = VK_ESCAPE;
    }
    else if (key == NKey::Space)
    {
        KeyWin = VK_SPACE;
    }
    else if (key == NKey::Enter)
    {
        KeyWin = VK_RETURN;
    }
    else if (key == NKey::LMB)
    {
        KeyWin = VK_LBUTTON;
    }
    else if (key == NKey::MMB)
    {
        KeyWin = VK_MBUTTON;
    }
    else if (key == NKey::RMB)
    {
        KeyWin = VK_RBUTTON;
    }
    return KeyWin;
}