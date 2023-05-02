#pragma once
struct tagMSG;
typedef tagMSG MSG;

struct MouseEvent
{
    enum Type {
        LPRESS,
        LRELEASE,
        RPRESS,
        RRELESE,
        MOVE
    };
};


class EventSystem {
public:
    EventSystem() = default;
    static uint HookMsg(const MSG* msg);
    static uint type;
    static uint state;
    static POINT pos;

    //--
    static POINT lastPos;
    static POINT delta;

    static bool IsKeyDown(int keyCode);
};