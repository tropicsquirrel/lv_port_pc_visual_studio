#include <lvgl.h>

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

extern int32_t tint_r;
extern int32_t tint_g;
extern int32_t tint_b;

//void event_handler_cb_progress_obj_red(lv_event_t* e);
//void event_handler_cb_progress_obj_green(lv_event_t* e);
//void event_handler_cb_progress_obj_blue(lv_event_t* e);
void set_color_panel(lv_event_t* e);
void load_scroll_color_values(lv_event_t* e);
void setup_cb(void);

#ifdef __cplusplus
}
#endif
