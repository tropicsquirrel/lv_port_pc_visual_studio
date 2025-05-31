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
    img = lv_label_create(objects.game1); //(lv_screen_active());
    lv_label_set_text(img, "");
    lv_obj_set_size(img, transform.bbWidth, transform.bbHeight); /*Set smaller width to make the lines wrap*/
    lv_obj_align(img, LV_ALIGN_CENTER, transform.x, transform.y);

    // Set object color
    lv_obj_set_style_bg_color(img, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_opa(img, LV_OPA_MAX, 0); // Something to do with opacity. Breaks if I remove it, so I'm leaving it here
}
void Object::Update()
{
    PhysicsUpdate();
    Render();
}
void Object::Render()
{
    lv_obj_set_pos(img, (int32_t)transform.x, (int32_t)transform.y);
}
void Object::PhysicsUpdate()
{
    Move(velocity.x, velocity.y);
    CheckBoundingBox();
}
void Object::CheckBoundingBox()
{
    // Check screen border
    if (transform.x - transform.bbWidth <= -125) // LEFT
    {
        transform.x = -125 + transform.bbWidth;
        velocity.x = 0;
    }
    if (transform.x + transform.bbWidth >= 125) // RIGHT
    {
        transform.x = 125 - transform.bbWidth;
        velocity.x = 0;
    }

    if (transform.y - transform.bbHeight <= -165) // TOP
    {
        transform.y = -165 + transform.bbHeight;
        velocity.y = 0;
    }
    if (transform.y + transform.bbHeight >= 165) // BOTTOM
    {
        transform.y = 165 - transform.bbHeight;
        velocity.y = 0;
    }

    printf("x: %f, y: %f\n", transform.x + transform.bbWidth, transform.y);

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
