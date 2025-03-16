#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *progress;
    lv_obj_t *mission;
    lv_obj_t *crew;
    lv_obj_t *info;
    lv_obj_t *settings;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *pip_right;
    lv_obj_t *pip_right_mid;
    lv_obj_t *pip_left_mid;
    lv_obj_t *pip_left;
    lv_obj_t *ctr_mission;
    lv_obj_t *obj2;
    lv_obj_t *ctr_crew;
    lv_obj_t *obj3;
    lv_obj_t *ctr_info;
    lv_obj_t *obj4;
    lv_obj_t *ctr_settings;
    lv_obj_t *obj5;
    lv_obj_t *ctr_progress;
    lv_obj_t *obj6;
    lv_obj_t *flavor_main1;
    lv_obj_t *flavor_main2;
    lv_obj_t *flavor_main3;
    lv_obj_t *flavor_main4;
    lv_obj_t *flavor_main5;
    lv_obj_t *flavor_main6;
    lv_obj_t *flavor_main7;
    lv_obj_t *flavor_side1;
    lv_obj_t *flavor_side2;
    lv_obj_t *flavor_side3;
    lv_obj_t *flavor_side4;
    lv_obj_t *obj7;
    lv_obj_t *ctr_progress_1;
    lv_obj_t *obj8;
    lv_obj_t *slider_red;
    lv_obj_t *slider_green;
    lv_obj_t *slider_blue;
    lv_obj_t *obj9;
    lv_obj_t *ctr_mission_1;
    lv_obj_t *obj10;
    lv_obj_t *ctr_crew_1;
    lv_obj_t *obj11;
    lv_obj_t *ctr_info_1;
    lv_obj_t *obj12;
    lv_obj_t *ctr_settings_1;
    lv_obj_t *obj13;
    lv_obj_t *ctr_settings_2;
    lv_obj_t *obj14;
    lv_obj_t *ctr_mission_3;
    lv_obj_t *obj15;
    lv_obj_t *panel_color;
    lv_obj_t *obj16;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_PROGRESS = 2,
    SCREEN_ID_MISSION = 3,
    SCREEN_ID_CREW = 4,
    SCREEN_ID_INFO = 5,
    SCREEN_ID_SETTINGS = 6,
};

void create_screen_main();
void tick_screen_main();

void create_screen_progress();
void tick_screen_progress();

void create_screen_mission();
void tick_screen_mission();

void create_screen_crew();
void tick_screen_crew();

void create_screen_info();
void tick_screen_info();

void create_screen_settings();
void tick_screen_settings();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/