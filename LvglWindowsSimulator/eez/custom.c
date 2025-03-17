#include "custom.h"
#include "screens.h"
#include "vars.h"

int32_t tint_r = 128; // Default value
int32_t tint_g = 128; // Default value
int32_t tint_b = 128; // Default value

// get/set red
int32_t get_var_tint_r() {
    return tint_r;
}
void set_var_tint_r(int32_t value) {
    tint_r = value;
}

// get/set green
int32_t get_var_tint_g() {
    return tint_g;
}
void set_var_tint_g(int32_t value) {
    tint_g = value;
}

// get/set blue
int32_t get_var_tint_b() {
    return tint_b;
}
void set_var_tint_b(int32_t value) {
    tint_b = value;
}

extern objects_t objects;

// set up callbacks for objects
void setup_cb()
{
    lv_obj_add_event_cb(objects.slider_red, set_color_panel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(objects.slider_green, set_color_panel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(objects.slider_blue, set_color_panel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(objects.progress, load_scroll_color_values, LV_EVENT_ALL, NULL);
}

// implement callback functions
void set_color_panel(lv_event_t* e) {
    lv_event_code_t event = lv_event_get_code(e);

    if (event == LV_EVENT_PRESSING)
    {
        if (objects.slider_red && objects.slider_green && objects.slider_blue)
        {
            int32_t red = lv_slider_get_value(objects.slider_red);
            int32_t green = lv_slider_get_value(objects.slider_green);
            int32_t blue = lv_slider_get_value(objects.slider_blue);
            if (objects.panel_color != NULL && lv_obj_is_valid(objects.panel_color)) {
                lv_obj_set_style_bg_color(objects.panel_color,
                    lv_color_make(red, green, blue),
                    LV_PART_MAIN);
            }
        }
    }
}

void load_scroll_color_values(lv_event_t* e)
{
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_SCREEN_LOADED) {
            if (objects.panel_color != NULL && lv_obj_is_valid(objects.panel_color)) {
                lv_obj_set_style_bg_color(objects.panel_color,
                    lv_color_make(tint_r, tint_g, tint_b),
                    LV_PART_MAIN);
                lv_slider_set_value(objects.slider_red, tint_r, LV_ANIM_OFF);
                lv_slider_set_value(objects.slider_green, tint_g, LV_ANIM_OFF);
                lv_slider_set_value(objects.slider_blue, tint_b, LV_ANIM_OFF);
            }
    }
}

//void event_handler_cb_progress_obj_red(lv_event_t* e) {
//    lv_event_code_t event = lv_event_get_code(e);
//
//    if (event == LV_EVENT_PRESSING) {
//        //void* flowState = lv_event_get_user_data(e);
//        //e->user_data = (void*)0;
//
//        // Add our color update code here
//        lv_obj_t* slider = lv_event_get_target(e);
//        if (slider != NULL && lv_obj_is_valid(slider)) {
//            int32_t value = lv_slider_get_value(slider);
//            if (objects.panel_color != NULL && lv_obj_is_valid(objects.panel_color)) {
//                lv_color_t color = lv_obj_get_style_bg_color(objects.panel_color, LV_PART_MAIN);
//                lv_obj_set_style_bg_color(objects.panel_color,
//                    lv_color_make(value, color.green, color.blue),
//                    LV_PART_MAIN);
//            }
//        }
//
//        // Original code
//        //flowPropagateValueLVGLEvent(flowState, 9, 0, e);
//    }
//}
//
//void event_handler_cb_progress_obj_green(lv_event_t* e) {
//    lv_event_code_t event = lv_event_get_code(e);
//
//    if (event == LV_EVENT_PRESSING) {
//        //void* flowState = lv_event_get_user_data(e);
//        //e->user_data = (void*)0;
//
//        // Add our color update code here
//        lv_obj_t* slider = lv_event_get_target(e);
//        if (slider != NULL && lv_obj_is_valid(slider)) {
//            int32_t value = lv_slider_get_value(slider);
//            if (objects.panel_color != NULL && lv_obj_is_valid(objects.panel_color)) {
//                lv_color_t color = lv_obj_get_style_bg_color(objects.panel_color, LV_PART_MAIN);
//                lv_obj_set_style_bg_color(objects.panel_color,
//                    lv_color_make(color.red, value, color.blue),
//                    LV_PART_MAIN);
//            }
//        }
//
//        // Original code
//        //flowPropagateValueLVGLEvent(flowState, 9, 0, e);
//    }
//}
//
//void event_handler_cb_progress_obj_blue(lv_event_t* e) {
//    lv_event_code_t event = lv_event_get_code(e);
//
//    if (event == LV_EVENT_PRESSING) {
//        //void* flowState = lv_event_get_user_data(e);
//        //e->user_data = (void*)0;
//
//        // Add our color update code here
//        lv_obj_t* slider = lv_event_get_target(e);
//        if (slider != NULL && lv_obj_is_valid(slider)) {
//            int32_t value = lv_slider_get_value(slider);
//            if (objects.panel_color != NULL && lv_obj_is_valid(objects.panel_color)) {
//                lv_color_t color = lv_obj_get_style_bg_color(objects.panel_color, LV_PART_MAIN);
//                lv_obj_set_style_bg_color(objects.panel_color,
//                    lv_color_make(color.red, color.green, value),
//                    LV_PART_MAIN);
//            }
//        }
//
//        // Original code
//        //flowPropagateValueLVGLEvent(flowState, 9, 0, e);
//    }
//}
