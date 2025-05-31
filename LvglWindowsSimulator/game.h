#pragma once

#include <vector>
#include "lvgl.h"
#include <string>

// Forward declaration
class Object;

// -------------------- Structs --------------------
struct Transform
{
    float x{ 0 };
    float y{ 0 };
    int bbWidth{ 50 };
    int bbHeight{ 50 };

    Transform(float nx = 0, float ny = 0, int nbbWidth = 10, int nbbHeight = 10)
        : x(nx), y(ny), bbWidth(nbbWidth), bbHeight(nbbHeight) {}
};

struct Velocity
{
    float x{ 0 };
    float y{ 0 };

    Velocity(int nx = 0, int ny = 0) : x(nx), y(ny) {}
};

// -------------------- Game Class --------------------
class cl_Game
{
protected:
    float gravity;
    std::vector<Object*> objects;
    int objCount;

public:
    cl_Game();
    cl_Game(int count);
    Object* OverlapBox(Object& obj);       // Returns first overlapping object (or nullptr)
    Object* OverlapBox(Transform& t);      // Overlaps at a point (or nullptr)

    float GetGravity() const { return gravity; }
    void SetGravity(float g) { gravity = g; }

    void AddObject(Object* obj) { objects.push_back(obj); }
    Object* GetObject(int idx) { return objects[idx]; }

    void RenderScene();
    virtual void Setup();
    virtual void Update();

    bool setup = false;
    //Object* GetObject(int i) { return objects[i]; }

    //virtual void GameInput(lv_event_t* e);
};

// -------------------- Object Class --------------------
class Object
{
protected:
    cl_Game* gameInst;
    Velocity velocity;

    void Render();
    void PhysicsUpdate();
    void CheckBoundingBox();

public:
    Object();
    Object(cl_Game& parentGame);
    //Object(cl_Game& parentGame, lv_obj_t* screen);
    void Move(float dx, float dy);
    void AddForce(float x, float y);
    void Update();

    std::string name;
    lv_obj_t* img;
    Transform transform;

};
