#pragma once
#include "game.h"
class g_game1 : public cl_Game
{
private:
    int tick = 0;
    Object o1;

public:
    g_game1();
    static void PlayerInput(lv_event_t* e);
    void Setup() override;
    void Update() override;
};
