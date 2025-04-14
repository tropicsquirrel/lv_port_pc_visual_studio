#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *avatar;
    lv_obj_t *pip_right;
    lv_obj_t *pip_right_mid;
    lv_obj_t *pip_left_mid;
    lv_obj_t *pip_left;
    lv_obj_t *ctr_mission;
    lv_obj_t *obj0;
    lv_obj_t *ctr_crew;
    lv_obj_t *obj1;
    lv_obj_t *ctr_info;
    lv_obj_t *obj2;
    lv_obj_t *ctr_settings;
    lv_obj_t *obj3;
    lv_obj_t *ctr_home;
    lv_obj_t *obj4;
    lv_obj_t *ctr_profile;
    lv_obj_t *btn_profile_main;
    lv_obj_t *lbl_random_numbers;
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
    lv_obj_t *btn_avatar;
    lv_obj_t *roller_avatar_component;
    lv_obj_t *ctr_mission_9;
    lv_obj_t *obj5;
    lv_obj_t *ctr_crew_7;
    lv_obj_t *obj6;
    lv_obj_t *ctr_info_7;
    lv_obj_t *obj7;
    lv_obj_t *ctr_settings_7;
    lv_obj_t *obj8;
    lv_obj_t *ctr_home_1;
    lv_obj_t *ctr_profile_7;
    lv_obj_t *lbl_random_numbers_1;
    lv_obj_t *tmp;
    lv_obj_t *img_background;
    lv_obj_t *img_body;
    lv_obj_t *img_clothes;
    lv_obj_t *img_head;
    lv_obj_t *img_mouth;
    lv_obj_t *img_beard;
    lv_obj_t *img_moustache;
    lv_obj_t *img_eye_left;
    lv_obj_t *img_nose;
    lv_obj_t *img_eye_right;
    lv_obj_t *img_hair;
    lv_obj_t *img_ears;
    lv_obj_t *img_ridges;
    lv_obj_t *img_eyebrow_left;
    lv_obj_t *img_eyebrow_right;
    lv_obj_t *img_borg;
    lv_obj_t *img_accessories;
    lv_obj_t *img_antennae;
    lv_obj_t *img_glasses;
    lv_obj_t *img_hands;
    lv_obj_t *slider_avatar_red;
    lv_obj_t *slider_avatar_green;
    lv_obj_t *slider_avatar_blue;
    lv_obj_t *slider_avatar_intensity;
    lv_obj_t *obj9;
    lv_obj_t *btn_avatar_prev;
    lv_obj_t *obj10;
    lv_obj_t *btn_avatar_next;
    lv_obj_t *lbl_avatar_item_id;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_AVATAR = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_avatar();
void tick_screen_avatar();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
