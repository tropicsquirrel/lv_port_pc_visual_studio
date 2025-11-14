#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *asd;
    lv_obj_t *main_tabview;
    lv_obj_t *main_tab_bar;
    lv_obj_t *main_tab_content;
    lv_obj_t *main_tab_stat;
    lv_obj_t *main_tab_inv;
    lv_obj_t *main_tab_data;
    lv_obj_t *main_tab_map;
    lv_obj_t *main_tab_radio;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_ASD = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_asd();
void tick_screen_asd();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/