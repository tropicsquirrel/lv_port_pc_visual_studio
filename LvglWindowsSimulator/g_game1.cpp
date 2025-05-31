#include "game.h"
#include "g_game1.h"
#include "custom.h"
#include "screens.h"

extern objects_t objects;

g_game1::g_game1()
{
    game_master = new cl_Game();
}

void g_game1::PlayerInput(lv_event_t* e)
{
    if (game_master == nullptr)
        return;
    if (game_master->GetObject(0) == nullptr)
        return;

    if (static_cast<char*>(lv_event_get_user_data(e)) == "l")
    {
        game_master->GetObject(0)->AddForce(-1, -3); // get player (always obj 0)
        printf("Input left\n");
    }
    else
    {
        game_master->GetObject(0)->AddForce(1, -3); // get player (always obj 0)
        printf("Input right\n");
    }
};

void g_game1::Setup()
{
    // Add objects to game
    o1 = Object(*game_master);
    game_master->AddObject(&o1);

    tick = 0;
    setup = true;
}

void g_game1::Update()
{
    tick++;
    if (tick % 5 == 0)
    {
        tick = 0;
        o1.AddForce(0, .25);
        RenderScene();
    }
}
