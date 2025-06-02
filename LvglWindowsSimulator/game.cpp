#include <vector>
#include "game.h"
#include "lvgl.h"
#include "screens.h"

extern objects_t objects;

//          ----------GAME CLASS----------
cl_Game::cl_Game()
{
    objCount = 0;
    objects.resize(0);
}
cl_Game::cl_Game(int count)
{
    objCount = count;
    objects.resize(objCount);
}
Object* cl_Game::OverlapBox(Object& obj)
{
    // code
    return nullptr;
}
Object* cl_Game::OverlapBox(Transform& t)
{
    // code
    return nullptr;
}
void cl_Game::RenderScene()
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (NULL == objects[i])
            return;

        objects[i]->Update();
    }
}
void cl_Game::Setup()
{
    setup = true;
}
void cl_Game::Update()
{
    printf("Update game master");
}
void cl_Game::AddScore(int val)
{
    score += val;
}

//          ----------OBJECT CLASS----------
Object::Object() // default constructor for game array
{
    gameInst = nullptr;
}
Object::Object(cl_Game& parentGame)
{
    transform = Transform();
    velocity = Velocity();
    gameInst = &parentGame;

    // Setup rendering
    img = lv_label_create(::objects.game1); //(lv_screen_active());
    lv_label_set_text(img, "");
    lv_obj_set_size(img, transform.pxWidth, transform.pxHeight); /*Set smaller width to make the lines wrap*/
    lv_obj_align(img, LV_ALIGN_CENTER, transform.x, transform.y);

    // Set object color
    lv_obj_set_style_bg_color(img, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_opa(img, LV_OPA_MAX, 0); // Something to do with opacity. Breaks if I remove it, so I'm leaving it here
}
Object::Object(lv_obj_t* screen, cl_Game& parentGame, const char* imgSource)
{
    transform = Transform();
    velocity = Velocity();
    gameInst = &parentGame;

    // Setup rendering
    img = lv_img_create(screen);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_img_set_src(img, imgSource);
    lv_obj_align(img, LV_ALIGN_CENTER, transform.x, transform.y);
    lv_obj_set_size(img, transform.pxWidth, transform.pxHeight); /*Set smaller width to make the lines wrap*/

    //lv_obj_set_style_bg_color(img, lv_color_hex(0xFF0000), 0);
    //lv_obj_set_style_bg_opa(img, LV_OPA_MAX, 0);
}
void Object::Update()
{
    PhysicsUpdate();
    Render();
}
void Object::Render()
{
    lv_obj_set_pos(img, transform.x, transform.y);
}
void Object::PhysicsUpdate()
{
    Move(velocity.x, velocity.y);
    CheckBoundingBox();
}
void Object::CheckBoundingBox()
{
    prev_velocity = Velocity(velocity);

    // Check screen border
    if (transform.x - (transform.pxWidth / 2) <= -120) // LEFT
    {
        transform.x = -120 + (transform.pxWidth / 2);
        velocity.x = 0;
    }
    if (transform.x + (transform.pxWidth / 2) >= 120) // RIGHT
    {
        transform.x = 120 - (transform.pxWidth / 2);
        velocity.x = 0;
    }

    if (transform.y - (transform.pxHeight / 2) <= -160) // TOP
    {
        transform.y = -160 + (transform.pxHeight / 2);
        velocity.y = 0;
    }
    if (transform.y + (transform.pxHeight / 2) >= 160) // BOTTOM
    {
        transform.y = 160 - (transform.pxHeight / 2);
        velocity.y = 0;
    }

    Object* hit = gameInst->OverlapBox(*this);
    if (hit == nullptr)
        return;

}
void Object::Move(float dx, float dy)
{
    transform.x += dx;
    transform.y += dy;
}
void Object::AddForce(float x, float y)
{
    velocity.x += x;
    velocity.y += y;
}
void Object::SetSize(int wid, int hei)
{
    transform.pxWidth = wid;
    transform.pxHeight = hei;
    lv_obj_set_size(img, transform.pxWidth, transform.pxHeight);
}
void Object::SetPos(int x, int y)
{
    transform.x = x;
    transform.y = y;
    lv_obj_set_pos(img, transform.x, transform.y);
}
