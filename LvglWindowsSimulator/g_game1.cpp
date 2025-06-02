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
    if (game_master->GetObject(1) == nullptr)
        return;

    game_master->AddScore(10);
    printf("Score: %d\n", game_master->GetScore());

    if (static_cast<char*>(lv_event_get_user_data(e)) == "l")
    {
        game_master->GetObject(1)->AddForce(-1, -3); // get player (always obj 1)
        printf("Input left\n");
    }
    else
    {
        game_master->GetObject(1)->AddForce(1, -3); // get player (always obj 1)
        printf("Input right\n");
    }
};

void g_game1::Setup()
{
    // Add objects to game
    bg = Object(::objects.game1, *game_master, "L:/images/g1/bg.png");
    bg.SetSize(240, 320);

    player = Object(::objects.game1, *game_master, "L:/images/g1/player.png");
    player.SetSize(28, 26);

    landingpad = Object(::objects.game1, *game_master, "L:/images/g1/landingpad.png");
    landingpad.SetSize(64, 16);
    landingpad.SetPos(0, 160);

    /*test_obj = Object(::objects.game1, *game_master, "L:/images/g1/test.png");
    test_obj.SetSize(32, 32);*/

    game_master->AddObject(&bg);
    game_master->AddObject(&player);
    game_master->AddObject(&landingpad);
    //game_master->AddObject(&test_obj);

    tick = 0;
    setup = true;
    score = 0;
}

void g_game1::Update()
{
    if (!running)
        return;

    tick++;
    if (tick % 5 == 0)
    {
        if (player.transform.y + (player.transform.pxHeight / 2) >= 145)
        {
            printf("pos %f, %f  --  vel-y %f\n", player.transform.x, player.transform.y, player.prev_velocity.y);
            if (player.prev_velocity.y < 1.5 && (player.transform.x <= 64 && player.transform.x >= -64)) printf("win\n");
            else printf("lose\n");
            running = false;
        }

        player.AddForce(0, .25);
        player.AddForce(-player.velocity.x * .05, -player.velocity.y * .02);

        RenderScene();
        tick = 0;
    }
}
