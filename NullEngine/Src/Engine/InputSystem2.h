#pragma once
#include <Core/Singleton.h>
#include <Math/vec2f.h>
#include <Math/rect.h>

enum class NKey
{
    Escape = 0,
    Shift,
    Space,
    Enter,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    N0,
    N1,
    N2,
    N3,
    N4,
    N5,
    N6,
    N7,
    N8,
    N9,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    LMB,
    MMB,
    RMB
};

class InputSystem2 : public Singleton<InputSystem2>
{
public:
    InputSystem2();
    ~InputSystem2();
public:
    void Update();

    bool GetKeyDown(const NKey& key);
    bool GetKeyUp(const NKey& key);
    bool GetKey(const NKey& key);

    void LockCursor(bool lock);
    void SetLockArea(const rect& Area);
    float GetAxis(const char* axis);


    vec2f GetDeltaMouse();
private:
    short GetInternalKeyCode(const NKey& key);
    short m_keyState[256] = {};
    short m_oldKeyState[256] = {};
    short m_finalKeyState[256] = {};

    float horizontalAxis = 0.0f;
    float verticalAxis = 0.0f;

    bool cursorLocked = false;
    rect lockArea;
    vec2f lockAreaCenter;
    vec2f oldMousePosition;
    vec2f deltaMousePosition;
};


